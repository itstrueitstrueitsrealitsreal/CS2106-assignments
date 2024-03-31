#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "llist.h"
TNode* get_memlist();
void print_node(TNode *node);
void merge_free(TNode *node);

char _heap[MEMSIZE] = {0};
TNode *_memlist = NULL; // To maintain information about length
TNode *last = NULL;

// Do not change this. Used by the test harness.
// You may however use this function in your code if necessary.
long get_index(void *ptr) {
    if(ptr == NULL)
        return -1;
    else
        return (long) ((char *) ptr - &_heap[0]);
}

void print_memlist() {
    process_list(get_memlist(), print_node);
}

// Allocates size bytes of memory and returns a pointer
// to the first byte.
void *mymalloc(size_t size) {
    TNode *llist = get_memlist();
    TNode *curr = last ? last : llist;
    // Traverse the list starting from the last allocated block
    do {
        if (curr->pdata->isAllocated == 0 && curr->pdata->len >= size) {
            // Found a suitable memory block
            // Split the node if necessary
            if (curr->pdata->len > size) {
                TData *data = malloc(sizeof(TData));
                data->len = curr->pdata->len - size;
                data->isAllocated = 0;
                TNode *node = make_node(curr->key + size, data);
                insert_node(&curr, node, ASCENDING);
                curr->pdata->len = size;
            }
            // Mark the memory block as allocated
            curr->pdata->isAllocated = 1;
            // Update the last allocated block
            last = curr;
            return &_heap[curr->key];
        }
        curr = curr->next; // Move to the next node
        if (curr == NULL) { // If the end of the list is reached, wrap around to the beginning
            reset_traverser(llist, FRONT);
            curr = llist;
        }
    } while (curr->key != last->key); // Continue until we reach the last allocated block again

    return NULL;
}

// Frees memory pointer to by ptr.
void myfree(void *ptr) {
    TNode *curr = get_memlist();
    curr = find_node(curr, get_index(ptr));
    if (curr != NULL) {
        curr->pdata->isAllocated = 0;
    }
    // traverse through list, merge adjacent free nodes
    process_list(_memlist, merge_free);
}


TNode* create_memlist() {
    TData *data = malloc(sizeof(TData));
    data->len = MEMSIZE;
    data->isAllocated = 0;
    TNode *node = make_node(0, data);
    insert_node(&_memlist, node, ASCENDING);
    return _memlist;
}

TNode* get_memlist() {
    if (_memlist == NULL) {
        return create_memlist();
    }
    return _memlist;
}

void print_node(TNode *node) {
    if (node != NULL) {
        if (node->pdata->isAllocated) {
            printf("Status: ALLOCATED Start index: %d Length: %d\n", node->key, node->pdata->len);
        } else {
            printf("Status: FREE Start index: %d Length: %d\n", node->key, node->pdata->len);
        }
    }
}

void merge_free(TNode *node) {
    if (node != NULL && node->pdata->isAllocated == 0) {
        TNode *next = node->next;
        while (next != NULL && next->pdata->isAllocated == 0) {
            merge_node(_memlist, node, REAR);
            next = node->next;
        }
    }
}

