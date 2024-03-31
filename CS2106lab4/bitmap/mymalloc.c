#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "bitmap.h"
#include "llist.h"
char _heap[MEMSIZE] = {0};
TNode *_memlist = NULL; // To maintain information about length

// Do not change this. Used by the test harness.
// You may however use this function in your code if necessary.
long get_index(void *ptr) {
    if(ptr == NULL)
        return -1;
    else
        return (long) ((char *) ptr - &_heap[0]);
}

void print_memlist() {
    // Implement this to call print_map from bitmap.c
    print_map((unsigned char *)_heap, MEMSIZE / 8);
}

// Allocates size bytes of memory and returns a pointer
// to the first byte.
void *mymalloc(size_t size) {
    int idx = search_map((unsigned char *) _heap, MEMSIZE / 8 , size);
    if (idx == -1) {
        return NULL;
    }
    allocate_map((unsigned char *)_heap, idx, size);
    TData* data = malloc(sizeof(TData));
    data->len = size;
    TNode* node = make_node(idx, data);
    insert_node(&_memlist, node, ASCENDING);
    return _heap + idx;
}

// Frees memory pointer to by ptr.
void myfree(void *ptr) {
    int idx = get_index(ptr);
    TNode *node = find_node(_memlist, idx);
    if (ptr == NULL || node == NULL || idx == -1) {
        return;
    }
    free_map((unsigned char *)_heap, idx, node->pdata->len);
    free(node->pdata);
    delete_node(&_memlist, node);
}
