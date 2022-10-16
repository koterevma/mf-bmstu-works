#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "customalloc.h"


#define MEM_SIZE 1000
#define ARRAY_SIZE 10


void test_one_allocation(Allocator* allocator) {
    bool success = true;
    fprintf(stderr, "\n%s:\n", __FUNCTION__);

    fprintf(stderr, "\tAvailable size: %d\n", remaining_space(allocator));
    fprintf(stderr, "\tAllocating array, of size %d * %d = %d\n", ARRAY_SIZE, (int)sizeof(int), ARRAY_SIZE * (int)sizeof(int));

    int* array = NULL;
    array = mem_alloc(allocator, ARRAY_SIZE * sizeof(int));

    fprintf(stderr, "\tAvailable size: %d\n", remaining_space(allocator));

    if (!array) {
        success = false;
    } else {
        fprintf(stderr, "\tNulling array\n");
        for (unsigned short i = 0; i < ARRAY_SIZE; ++i) {
            array[i] = 0;
        }
        fprintf(stderr, "\tDealocating memory back\n");
        mem_free(allocator, array);
        fprintf(stderr, "\tAvailable size: %d\n", remaining_space(allocator));
    }

    fprintf(stderr, __FUNCTION__);
    if (success)
        fprintf(stderr, " SUCCESS\n");
    else
        fprintf(stderr, " FAILURE\n");
}

void test_multiple_allocations(Allocator* allocator) {
    bool success = true;

    fprintf(stderr, "\n%s:\n", __FUNCTION__);
    fprintf(stderr, "\tAvailable size: %d\n", remaining_space(allocator));
    fprintf(stderr, "\tAllocating 2 arrays, of size 2 * %d * %d = %d\n", ARRAY_SIZE, (int)sizeof(int), 2 * ARRAY_SIZE * (int)sizeof(int));

    void* unused1 = mem_alloc(allocator, ARRAY_SIZE * sizeof(int));
    void* unused2 = mem_alloc(allocator, ARRAY_SIZE * sizeof(int));

    fprintf(stderr, "\tAvailable size: %d\n", remaining_space(allocator));

    if (!unused1 || !unused2)
        success = false;
    else {
        fprintf(stderr, "\tDealocating memory back\n");
        mem_free(allocator, unused1);
        mem_free(allocator, unused2);
        fprintf(stderr, "\tAvailable size: %d\n", remaining_space(allocator));
    }
    fprintf(stderr, __FUNCTION__);
    if (success)
        fprintf(stderr, " SUCCESS\n");
    else
        fprintf(stderr, " FAILURE\n");

}

int main() {
    Allocator* allocator = init_alloc(MEM_SIZE);

    test_one_allocation(allocator);
    test_multiple_allocations(allocator);

    destroy_alloc(allocator);
    return 0;
}
