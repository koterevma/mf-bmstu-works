#include "customalloc.h"
#include <stddef.h>
#include <malloc.h>


CustomAlloc* InitAlloc(int size) {
    CustomAlloc* customAlloc = (CustomAlloc*)malloc(sizeof(CustomAlloc));
    customAlloc->PoolSize = size;
    customAlloc->MemoryPool = (char*) malloc(size * sizeof(char));
    customAlloc->BitMap = (bool*) calloc(sizeof(bool), size);

    for (int i = 0; i < size; ++i) {
        customAlloc->BitMap[i] = false;
    }

    return customAlloc;
}

void* CustomMalloc(CustomAlloc* customAlloc, int size) {
    int current_chunk_len = 0;
    void* found_chunk = NULL;
    for (int i = 0; i < customAlloc->PoolSize; ++i) {
        if (!customAlloc->BitMap[i] && current_chunk_len == 0)
            found_chunk = customAlloc->MemoryPool + i;

        if (!customAlloc->BitMap[i]) {
            ++current_chunk_len;
        } else {
            current_chunk_len = 0;
        }
        
        if (current_chunk_len >= size)
            break;
    }

    if (found_chunk == NULL)
        return found_chunk;

    int initial_offset = (char*) found_chunk - customAlloc->MemoryPool;
    for (int i = initial_offset; i < initial_offset + size; ++i) {
        customAlloc->BitMap[i] = true;
    }

    return found_chunk;
}

void CustomFree(CustomAlloc* customAlloc, void* mem, int size) {
    int initial_offset =  (char*) mem - customAlloc->MemoryPool;
    for (int i = initial_offset; i < initial_offset + size; ++i) {
        customAlloc->BitMap[i] = false;
    }
}

int RemainingFreeSpace(CustomAlloc* customAlloc) {
    int s = 0;
    for (int i = 0; i < customAlloc->PoolSize; ++i) {
        if (!customAlloc->BitMap[i])
            ++s;
    }
    return s;
}

void DestroyAlloc(CustomAlloc* customAlloc) {
    free(customAlloc->BitMap);
    free(customAlloc->MemoryPool);
    free(customAlloc);
}
