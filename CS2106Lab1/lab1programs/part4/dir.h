#include "llist.h"

// Add prototypes and other declarations below
void writelog(char *);

void init_hashtable(TLinkedList *hashtable[], int len);

TLinkedList *get_filelist(char *, int (*)(char *, int), TLinkedList *[], int );

void update_hashtable(char *, int (*)(char *, int),
                      TLinkedList *[], int, TLinkedList *);

TLinkedList *find_file(char *, int (*)(char *, int), TLinkedList *[], int);

void add_file(char *, int, int, int (*)(char *, int), TLinkedList *[], int);

void delete_file(char *, int (*)(char *, int), TLinkedList *[], int );

void rename_file(char *, char *, int (*)(char *, int),
                 TLinkedList *[], int);

void print_node(TLinkedList *);

void listdir(TLinkedList *[], int );