#include <stddef.h>
#include <stdio.h>
#include "list.h"
#include "customalloc.h"

ListP InitList(CustomAlloc* customAlloc, int size) {
    int value = 0;
    ListP head = (ListP) CustomMalloc(customAlloc, sizeof(List));
    head->value = ++value;
    head->next = NULL;
    size--;

    for (ListP elem = head; size; --size) {
        ListP next_elem = (ListP) CustomMalloc(customAlloc, sizeof(List));
        elem->next = next_elem;
        next_elem->next = NULL;
        next_elem->value = ++value;

        elem = next_elem;
    }

    return head;
}

void PrintList(ListP head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

ListP TailOfList(ListP head) {
    while (head->next) {
        head = head->next;
    }

    return head;
}

void PopTail(CustomAlloc* customAlloc, ListP head) {
    ListP tail = TailOfList(head);
    while (head->next != tail) {
        head = head->next;
    }

    head->next = NULL;

    CustomFree(customAlloc, tail, sizeof(List));
}

ListP PopHead(CustomAlloc* customAlloc, ListP head) {
    ListP next_head = head->next;

    CustomFree(customAlloc, head, sizeof(List));
    return next_head;
}
