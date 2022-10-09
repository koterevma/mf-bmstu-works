#include <stdio.h>
#include <stdlib.h>
#include "customalloc.h"

#define MAX_ALLOC_SIZE 1000

int main(int argc, char* argv[]) {
    int size1 = 30; // Array N
    int size2 = 16; // Matrix N*N

    CustomAlloc customAlloc;
    InitAlloc(&customAlloc, MAX_ALLOC_SIZE);

    fprintf(stderr, "Allocating %d bytes for array of char\n", size1);

    char* testData = CustomMalloc(&customAlloc, size1);

    fprintf(stderr, "Testing allocated chars\n");

    char c = 'a';
    for(int i = 0; i < size1 - 1; ++i) {
        testData[i] = c++;
    }
    testData[size1 - 1] = '\0';
    printf("%s\n", testData);

    fprintf(stderr, "Remaining allocator memory: %d\n", RemainingFreeSpace(&customAlloc));
    fprintf(stderr, "\n");

    fprintf(stderr, "Allocating new data %d * %d bytes\n", size2, size2);

    char* testMatrix[16];
    c = 'a';
    for (int i = 0; i < size2; ++i) {
        testMatrix[i] = CustomMalloc(&customAlloc, size2);
        char cc = c;
        for (int j = 0; j < size2; ++j) {
            testMatrix[i][j] = cc++;
        }
        c++;
    }

    for (int i = 0; i < size2; ++i) {
        for (int j = 0; j < size2; ++j) {
            printf("%c", testMatrix[i][j]);
        }
        printf("\n");
    }

    unsigned remainingMemory = RemainingFreeSpace(&customAlloc);
    fprintf(stderr, "Remaining allocator memory: %d\n", remainingMemory);
    fprintf(stderr, "\n");

    fprintf(stderr, "Allocating all remaining memory\n");
    void* tempPointer = CustomMalloc(&customAlloc, remainingMemory);

    fprintf(stderr, "Remaining allocator memory: %d\n", RemainingFreeSpace(&customAlloc));
    fprintf(stderr, "\n");

    void* shouldBeNullptr = CustomMalloc(&customAlloc, 256);
    if (shouldBeNullptr) {
        fprintf(stderr, "Allocated memory. It shouldn't\n");
#ifdef DEBUG
        abort();
#else
        return 1;
#endif
    }

    fprintf(stderr, "Deallocating %d * %d bytes\n", size2, size2);

    for (int i = 0; i < size2; ++i) {
        CustomFree(&customAlloc, testMatrix[i], size2);
    }

    remainingMemory = RemainingFreeSpace(&customAlloc);
    fprintf(stderr, "Remaining allocator memory: %d\n", remainingMemory);
    fprintf(stderr, "\n");

    fprintf(stderr, "Trying allocate %lu bytes\n", remainingMemory - sizeof(List));

    tempPointer = CustomMalloc(&customAlloc, remainingMemory - sizeof(List));
    if (!tempPointer) {
        fprintf(stderr, "Didn't alocate memory. It should\n");
#ifdef DEBUG
        abort();
#else
        return 1;
#endif
    }

    remainingMemory = RemainingFreeSpace(&customAlloc);
    fprintf(stderr, "Remaining allocator memory: %d\n", remainingMemory);
    fprintf(stderr, "\n");

    fprintf(stderr, "Deallocating array of %d bytes\n", size1);

    CustomFree(&customAlloc, testData, size1);

    fprintf(stderr, "Remaining allocator memory: %d\n", RemainingFreeSpace(&customAlloc));
    fprintf(stderr, "\n");

    DestroyAlloc(&customAlloc);

    return 0;
}
