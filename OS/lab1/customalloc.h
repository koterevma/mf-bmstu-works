#ifndef CUSTOMALLOC_H
#define CUSTOMALLOC_H
#include <stdbool.h>

typedef struct CustomAlloc {
    int PoolSize;
    char* MemoryPool;
    bool* BitMap;
} CustomAlloc;

CustomAlloc* InitAlloc(int size);

void* CustomMalloc(CustomAlloc* customAlloc, int size);

void CustomFree(CustomAlloc* customAlloc, void* mem, int size);

int RemainingFreeSpace(CustomAlloc* customAlloc);

void DestroyAlloc(CustomAlloc* customAlloc);

#endif
