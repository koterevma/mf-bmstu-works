#ifndef CUSTOMALLOC_H
#define CUSTOMALLOC_H

struct List;
typedef struct List List;
typedef List* ListP;

struct List {
    ListP next;
    unsigned size;
};

typedef struct CustomAlloc {
    ListP head;
    void* mempool;
} CustomAlloc;

void InitAlloc(CustomAlloc* customAlloc, unsigned size);

void* CustomMalloc(CustomAlloc* customAlloc, unsigned size);

void CustomFree(CustomAlloc* customAlloc, void* mem, unsigned size);

unsigned RemainingFreeSpace(CustomAlloc* customAlloc);

void DestroyAlloc(CustomAlloc* customAlloc);

#endif
