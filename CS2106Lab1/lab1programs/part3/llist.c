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
    TLinkedList *newNode = (TLinkedList *) malloc(sizeof(TLinkedList));

    strncpy(newNode->filename, filename, MAX_FNAME_LEN - 1);
    newNode->filesize = filesize;
    newNode->startblock = startblock;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

// Insert node into the end of the linkedlist indicated by head
// PRE: head = Pointer variable pointing to the start of the linked list
//      node = Node created using create_node
// POST: node is inserted into the linked list.

void insert_llist(TLinkedList **head, TLinkedList *node) {
    if (*head == NULL) {
        *head = node;
    } else {
        TLinkedList *trav = *head;

        // traverse through the list
        while (trav->next != NULL) {
            trav = trav->next;
        }

        // update pointers for the last node and the second last node
        trav->next = node;
        node->prev = trav;
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
    free(node->filename);
    free(node);
}


// Find node in the linkedlist
// PRE: head = Variable that points to the first node of the linked list
//      fname = Name of file to look for
// RETURNS: The node that contains fname, or NULL if not found.
TLinkedList *find_llist(TLinkedList *head, char *fname) {
    // traverse through linkedlist till node with matching filename is found
    TLinkedList *curr = head;
    while (curr != NULL && strcmp(curr->filename, fname)) {
        curr = curr->next;
    }
    return curr;
}

// Traverse the entire linked list calling a function
// PRE: head = Variable pointing to the first node of the linked list
//      fn = Pointer to function to be called for each node
// POST: fn is called with every node of the linked list.

void traverse(TLinkedList **head, void (*fn)(TLinkedList *)) {
    TLinkedList *curr = *head;
    while (curr != NULL) {
        fn(curr);
        curr = curr->next;
    }
}

