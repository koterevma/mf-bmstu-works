#include "customalloc.h"
#include <stddef.h>
#include <malloc.h>
#include <stdio.h>

typedef unsigned short Tag;
// 0b1000000000000000
#define MASK_FREE 0x8000
// 0b0111111111111111
#define MASK_SIZE 0x7FFF
// Same as MASK_SIZE
#define MAX_ALLOC_SIZE 0x7FFF

typedef struct List List;

struct List {
    List* next;
    List* prev;
};

typedef struct _Allocator {
    List* head;
    void* memstart;
} Allocator;

static Tag* get_tag(void* block) {
    return block - sizeof(Tag);
}

static void clean_holes(Allocator* allocator) {
    if (!allocator->head)
        return;

    List* block = allocator->head;
    while (block->next) {
        Tag* tag = get_tag(block);
        if ((void*)block + (*tag & MASK_SIZE) + sizeof(Tag) == block->next) {
            Tag* next_tag = get_tag(block->next);
            *tag = MASK_FREE | ((*tag & MASK_SIZE) + (*next_tag & MASK_SIZE) + sizeof(Tag));

            block->next = block->next->next;
            if (block->next)
                block->next->prev = block;
            continue;
        }
        block = block->next;
    }
}

static List* init_new_clean_block(void* memstart, unsigned short size) {
    Tag* tag = memstart;
    *tag = (size - sizeof(Tag)) & MASK_SIZE;
    *tag |= MASK_FREE;

    List* block = (List*) (memstart + sizeof(Tag));
    block->next = NULL;
    block->prev = NULL;

    return block;
}

Allocator* init_alloc(unsigned short size) {
    if (size > MAX_ALLOC_SIZE)
        return NULL;

    Allocator* allocator = malloc(sizeof(Allocator));
    allocator->memstart = malloc(size);

    List* head = init_new_clean_block(allocator->memstart, size);

    allocator->head = head;

    return allocator;
}

void* mem_alloc(Allocator* allocator, unsigned short size) {
    if (size > MAX_ALLOC_SIZE)
        return NULL;

    List* block = allocator->head;
    List* new_block = NULL;

    while (block) {
        Tag* tag = (Tag*) ((void*)block - sizeof(Tag));
        if ((*tag & MASK_FREE) && (*tag & MASK_SIZE) >= size + sizeof(Tag) + sizeof(List)) {
            new_block = init_new_clean_block((void*)block + size, (*tag & MASK_SIZE) - size);

            *tag = size;
            *tag &= ~MASK_FREE;

            break;
        }    
        block = block->next;
    }

    if (!new_block)
        return NULL;

    if (block == allocator->head) {
        allocator->head = new_block;
        new_block->next = block->next;
        return block;
    }

    if (block->prev) {
        block->prev->next = new_block;
        new_block->prev = block->prev;
    }
    if (block->next) {
        block->next->prev = new_block;
        new_block->next = block->next;
    }

    return block;
}

void mem_free(Allocator* allocator, void* mem) {
    Tag* tag = (Tag*) (mem - sizeof(Tag));
    *tag |= MASK_FREE;
    List* new_block = (List*) mem;
    List* block = allocator->head;

    if (!allocator->head) {
        allocator->head = new_block;
        return;
    }

    if (new_block < allocator->head) {
        new_block->next = allocator->head;
        allocator->head->prev = new_block;
        allocator->head = new_block;
        clean_holes(allocator);
        return;
    }

    while (block->next && block->next < new_block) {
        block = block->next;
    }

    if (block->next) {
        block->next->prev = new_block;
        new_block->next = block->next;
    }
    block->next = new_block;
    new_block->prev = block;

    clean_holes(allocator);
}

unsigned short remaining_space(Allocator* allocator) {
    unsigned short size = 0;
    List* head = allocator->head;
    while (head) {
        Tag* tag = (Tag*) ((void*)head - sizeof(Tag));
        if (*tag & MASK_FREE)
            size += (*tag & MASK_SIZE);
        head = head->next;
    }
    return size;
}

void destroy_alloc(Allocator* allocator) {
    free(allocator->memstart);
    free(allocator);
}
