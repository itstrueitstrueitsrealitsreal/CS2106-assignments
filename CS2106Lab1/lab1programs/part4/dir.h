#include "llist.h"

// Add prototypes and other declarations below
void writelog(char *)

// Initializes all entries of the hashtable to NULL
// PRE: hashtable = Hash table to be initialized
//      len = Number of entries in the hashtable.
//          The hash table is thus indexed from 0 to len-1
// POST: Every entry of the hash table is set to NULL.
//

void init_hashtable(TLinkedList *hashtable[], int len);

TLinkedList *get_filelist(char *, int (*hashfun)(char *, int), TLinkedList *hashtable[], int ) {
    int ndx = hashfun(filename, len);

    TLinkedList *filelist = hashtable[ndx];

    return filelist;
}

// Updates the head for a linked list that may contain filename.
// This is needed because llist may sometimes change the head
// variable. Thus this function must be called every time you
// insert or delete a file. This function is implemented for you.
//
// PRE: filename = Name of file
//      hashfun = Hash function
//      hashtable = Hash table
//      newentry = The head value returned by insert, delete
//          Note that this value may not necessarily change
//          but we should call update_hashtable anyway just in case.
//
// POST: newentry is written to hashtable[ndx], where ndx
//      is the index value returned by hashfun
//


void update_hashtable(char *filename, int (*hashfun)(char *, int),
                      TLinkedList *hashtable[], int len, TLinkedList *newentry) {

    int ndx = hashfun(filename, len);
    hashtable[ndx] = newentry;
}

// Find file and return node containing filename
// Use the functions in llist.c and the functions defined above
// to implement.
//
// PRE: filename = name of file to find.
//      hashfun = Hash function
//      hashtable = Hash table
//      len = # of entries in hash table.
//
// RETURNS: The TLinkedList node containing data on filename if found,
//          NULL otherwise. Note that we should not call writelog to
//          print an error if the file is not found because sometimes
//          this is what we want, e.g. when adding a new file.
//

TLinkedList *find_file(char *filename, int (*hashfun)(char *, int), TLinkedList *hashtable[], int len) {

}

// Add a new file
// PRE: filename = name of file to add
//      filesize = Size of file to add
//      startblock = Starting block number of file
//      hashfun = Hash function
//      hashtable = Hash table
//      len = # of entries in hash table
//
// POST: Error is printed if file exists. Otherwise a new node
//       is created and added to the appropriate linked list
//       HINT: Use get_filelist. Also remember that inserting
//              into a linked list may result in the head
//              being changed.
//


void add_file(char *filename, int filesize, int startblock,
}

// Delete file. Remove the file's entry from the directory
// PRE: filename = name of file to delete.
//      hashfun = Hash function
//      hashtable = Hash table
//      len = # of entries in hash table.
// POST: An error message if the file is not found.
//      Otherwise the file's entry is deleted.
//      HINT: The head might be changed.

void delete_file(char *filename, int (*hashfun)(char *, int), TLinkedList *hashtable[], int len) {

}

// Rename a file.
// PRE: old_filename = Current filename
//      new_filename = Name to change to
//      hashfun = Hash function
//      hashtable = Hash table
//      len = # of entries in hash table
// POST: Error message if old_filename is not found. Otherwise
//      The directory is updated with the new filename.
//

void rename_file(char *old_filename, char *new_filename, int (*hashfun)(char *, int),
                 TLinkedList *hashtable[], int len) {

}

// Prints the details of a file. Implemented for you.
// PRE: node = node to be printed.
// POST: The contents of node are printed.
void print_node(TLinkedList *node) {
    printf("%-30s\t\t%6d\t\t%6d\n", node->filename, node->filesize, node->startblock);
}

// List the directory. Does not need to be in any order.
// PRE: hashtable = Hash table
//      len = # of entries in hash table
// POST: List of files in hashtable is printed.
// HINT: You can treat hashtable as an array
//      and access its elements directly.
//      There is a useful function in llist that
//      traverses the linked list and applies a function
//      to it.

void listdir(TLinkedList *hashtable[], int len) {
    printf("\nFilename\t\t\tFile Size\t\tStart Block\n\n");

    // Implement the rest of this function below.

}