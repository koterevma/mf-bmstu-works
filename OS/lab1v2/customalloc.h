#ifndef CUSTOMALLOC_H
#define CUSTOMALLOC_H

typedef struct _Allocator Allocator;

Allocator* init_alloc(unsigned short size);
void* mem_alloc(Allocator* allocator, unsigned short size);
void mem_free(Allocator* allocator, void* mem);
unsigned short remaining_space(Allocator* allocator);
void destroy_alloc(Allocator* allocator);

#endif
