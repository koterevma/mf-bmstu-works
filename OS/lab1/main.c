#include <stdio.h>
#include <stdlib.h>
#include "customalloc.h"
#include "list.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Not enough args, argc < 2\n");
        return 1;
    }

    int size = atoi(argv[1]);

    fprintf(stderr, "Generating list of size %d\n", size);

    CustomAlloc* customAlloc = InitAlloc(size * sizeof(List));

    ListP list = InitList(customAlloc, size);

    PrintList(list);
    fprintf(stderr, "\n");

    fprintf(stderr, "Current available size of alloc is %d\n", RemainingFreeSpace(customAlloc));

    int deallocNum = size / 2;
    fprintf(stderr, "Deallocating %d elements, %lu bytes\n", deallocNum, sizeof(List) * deallocNum);

    for (int i = 0; i < deallocNum / 2; ++i) {
        list = PopHead(customAlloc, list);
    }

    for (int i = 0; i < deallocNum - deallocNum / 2; ++i) {
        PopTail(customAlloc, list);
    }

    PrintList(list);
    fprintf(stderr, "\n");

    int currentAvailableSize = RemainingFreeSpace(customAlloc);
    fprintf(stderr, "Current available size of alloc is %d\n", currentAvailableSize);

    int newListSize = currentAvailableSize / sizeof(List);
    fprintf(stderr, "Allocating new list of size %d\n", newListSize);

    ListP newList = InitList(customAlloc, newListSize);

    fprintf(stderr, "New list has been initialized\n");

    PrintList(newList);
    fprintf(stderr, "\n");

    fprintf(stderr, "Current available size of alloc is %d\n", RemainingFreeSpace(customAlloc));

    DestroyAlloc(customAlloc);
    return 0;
}
