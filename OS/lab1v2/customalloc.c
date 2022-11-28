#include "customalloc.h"
#include <stddef.h>
#include <malloc.h>
#include <stdbool.h>
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
    List* last_freed;
    void* memstart;
} Allocator;

static Tag* get_tag(void* block) {
    return block - sizeof(Tag);
}

static void clean_holes(Allocator* allocator, List* block) {
    if (!allocator->head)
        // We are out of free blocks - nothing to clean
        return;

    Tag* tag;
    if (block != allocator->head) {
        // Get prev block tag
        tag = get_tag((void*)block - sizeof(Tag));

        // If previous block is free
        if (tag & MASK_FREE) {
            List* prev_block = (void*) block - (*tag & MASK_SIZE) - sizeof(Tag);
            init_new_clean_block(prev_block, (*tag & MASK_SIZE) + (get_tag(block) & MASK_SIZE) + 2 * sizeof(Tag);
        }

        // Get next block tag
        tag = get_tag((void*)block + (get_tag(block) & MASK_SIZE) + 2 * sizeof(Tag));

        // If next block is free
        if (tag & MASK_FREE) {
            List* next_block = (void*) block + (*tag & MASK_SIZE) + 2 * sizeof(Tag);
            init_new_clean_block(block, (*tag & MASK_SIZE) + (get_tag(block) & MASK_SIZE) + 2 * sizeof(Tag);
        }
    }
}

static List* init_new_clean_block(void* memstart, unsigned short size) {
    Tag* tag = memstart;
    *tag = (size - sizeof(Tag) * 2) & MASK_SIZE;
    *tag |= MASK_FREE;

    List* block = (List*) (memstart + sizeof(Tag));
    block->next = NULL;
    block->prev = NULL;

    // Init second tag at the end of free block
    tag = memstart + size - sizeof(Tag);
    *tag = (size - sizeof(Tag) * 2) & MASK_SIZE;
    *tag |= MASK_FREE;

    return block;
}

Allocator* init_alloc(unsigned short size) {
    if (size > MAX_ALLOC_SIZE)
        return NULL;

    Allocator* allocator = malloc(sizeof(Allocator));
    allocator->memstart = malloc(size);
    allocator->last_freed = NULL;

    List* head = init_new_clean_block(allocator->memstart, size);

    allocator->head = head;

    return allocator;
}

void* mem_alloc(Allocator* allocator, unsigned short size) {
    if (size > MAX_ALLOC_SIZE)
        return NULL;

    List* block = allocator->head;
    if (!block) {
        return NULL;
    }

    bool started_from_last_freed = false;
    if (allocator->last_freed) {
        block = allocator->last_freed;

        started_from_last_freed = true;
    }
    List* new_block = NULL;

    while (block || started_from_last_freed) {
        if (!block) {
            block = allocator->head;
            started_from_last_freed = false;
        }

        Tag* tag = (Tag*) ((void*)block - sizeof(Tag));
        if ((*tag & MASK_FREE) && (*tag & MASK_SIZE) >= size + 2 * sizeof(Tag) + sizeof(List)) {
            new_block = init_new_clean_block((void*)block + size + 2 * sizeof(Tag), (*tag & MASK_SIZE) - size - sizeof(Tag));

            *tag = size;
            *tag &= ~MASK_FREE;

            tag = (Tag*) ((void*)block + size);

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
        allocator->last_freed = clean_holes(allocator, new_block);
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

    clean_holes(allocator, new_block);
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
