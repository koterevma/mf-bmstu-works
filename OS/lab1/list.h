#ifndef LIST_H
#define LIST_H

#include "customalloc.h"

struct List;
typedef struct List List;
typedef List* ListP;

struct List {
    ListP next;
    int value;
};

ListP InitList(CustomAlloc* customAlloc, int size);

void PrintList(ListP head);

ListP TailOfList(ListP head);

void PopTail(CustomAlloc* customAlloc, ListP head);

ListP PopHead(CustomAlloc* customAlloc, ListP head);

#endif
