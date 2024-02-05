// Implement a double linked-list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

// Initialize the linked list by setting head to NULL
// PRE: head is the pointer variable that points to the
//      first node of the linked list
// POST: head is set to NULL

void init_llist(TLinkedList **head) {
    // Set head to NULL
    *head = NULL;
}

// Create a new node
// PRE: filename = name of file to be inserted
//      filesize = size of file in blocks
//      startblock = File's starting block
// RETURNS: A new node containing the file information is created.

TLinkedList *create_node(char *filename, int filesize, int startblock) {
    TLinkedList *l = (TLinkedList *) malloc(sizeof(TLinkedList));
    l->filesize = filesize;
    l->startblock = startblock;
    strncpy(l->filename, filename, MAX_FNAME_LEN - 1);
    l->next = NULL;
    l->prev = NULL;
    return l;
}

// Insert node into the end of the linkedlist indicated by head
// PRE: head = Pointer variable pointing to the start of the linked list
//      node = Node created using create_node
// POST: node is inserted into the linked list.

void insert_llist(TLinkedList **head, TLinkedList *node) {
    if (*head == NULL) {
        // If the list is empty, set node as the head
        *head = node;
    } else {
        TLinkedList *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
        node->prev = current;
        node->next = NULL;
    }
}

// Delete node from the linkedlist
// PRE: head = Pointer variable pointing to the start of the linked list
//      node = An existing node in the linked list to be deleted.
// POST: node is deleted from the linked list
void delete_llist(TLinkedList **head, TLinkedList *node) {
    // If the node to be deleted is the head
    if (*head == node) {
        *head = node->next; // Update the head to the next node
    }

    // Update the next node's previous pointer
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    // Update the previous node's next pointer
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    free(node);
}


// Find node in the linkedlist
// PRE: head = Variable that points to the first node of the linked list
//      fname = Name of file to look for
// RETURNS: The node that contains fname, or NULL if not found.
TLinkedList *find_llist(TLinkedList *head, char *fname) {
    TLinkedList *node = head;
    while(node != NULL) {
        if(strcmp(node->filename, fname) == 0) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

// Traverse the entire linked list calling a function
// PRE: head = Variable pointing to the first node of the linked list
//      fn = Pointer to function to be called for each node
// POST: fn is called with every node of the linked list.

void traverse(TLinkedList **head, void (*fn)(TLinkedList *)) {
    TLinkedList *node = *head;
    while(node != NULL) {
        fn(node);
        node = node->next;
    }
}