#include "customalloc.h"
#include <stddef.h>
#include <malloc.h>
#include <stdio.h>


void CleanHoles(CustomAlloc* customAlloc) {
    ListP head = customAlloc->head;
    while (head) {
        if (head->next && head->next == head + head->size) {
            head->size += head->next->size;
            head->next = head->next->next;
        } else {
            head = head->next;
        }
    }
}

void InitAlloc(CustomAlloc* customAlloc, unsigned size) {
    size += sizeof(List);
    customAlloc->mempool = malloc(size);
    customAlloc->head = (ListP) customAlloc->mempool;
    customAlloc->head->size = size;
    customAlloc->head->next = NULL;
}

void* CustomMalloc(CustomAlloc* customAlloc, unsigned size) {
    ListP prevBlock = NULL;
    ListP blockP = customAlloc->head;

    while (blockP) {
        if (blockP->size >= size + sizeof(List)) {
            if (blockP == customAlloc->head) {
                customAlloc->head = blockP + size;
                customAlloc->head->size = blockP->size - size;
                customAlloc->head->next = blockP->next;
            } else {
                prevBlock->next = blockP + size;
                prevBlock->next->size = blockP->size - size;
                prevBlock->next->next = blockP->next;
            }
            return blockP;
        }

        prevBlock = blockP;
        blockP = blockP->next;
    }

    return NULL;
}

void CustomFree(CustomAlloc* customAlloc, void* mem, unsigned size) {
    ListP blockP = (ListP) mem;
    blockP->size = size;

    if ((void*) customAlloc->head > mem) {
        blockP->next = customAlloc->head;
        customAlloc->head = blockP;
    } else {
        ListP tempBlock = customAlloc->head;
        while (tempBlock->next && tempBlock->next < blockP) {
            tempBlock = tempBlock->next;
        }
        blockP->next = tempBlock->next;
        tempBlock->next = blockP;
    }
    CleanHoles(customAlloc);
}

unsigned RemainingFreeSpace(CustomAlloc* customAlloc) {
    unsigned s = 0;
    ListP tempBlock = customAlloc->head;
    while (tempBlock) {
        s += tempBlock->size;
        tempBlock = tempBlock->next;
    }
    return s -= sizeof(List);
}

void DestroyAlloc(CustomAlloc* customAlloc) {
    free(customAlloc->mempool);
    customAlloc->mempool = NULL;
    customAlloc->head = NULL;
}

void PrintAlloc(CustomAlloc* customAlloc) {
    ListP head = customAlloc->head;
    while (head) {
        printf("%d -> ", head->size);
        head = head->next;
    }
    printf("\n");
}
