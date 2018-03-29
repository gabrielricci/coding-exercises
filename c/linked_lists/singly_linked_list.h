#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

typedef struct node {
    int data;
    struct node* next;
} NODE;

typedef struct singly_linked_list {
    NODE* head;
    NODE* tail;
} SINGLY_LINKED_LIST;

SINGLY_LINKED_LIST* linked_list_create(int);
void linked_list_push_back(SINGLY_LINKED_LIST*, int);
void linked_list_push_front(SINGLY_LINKED_LIST*, int);
NODE* linked_list_pop_back(SINGLY_LINKED_LIST*);
NODE* linked_list_pop_front(SINGLY_LINKED_LIST*);
int linked_list_size(SINGLY_LINKED_LIST*);
int linked_list_empty(SINGLY_LINKED_LIST*);
NODE* linked_list_value_at(SINGLY_LINKED_LIST*, int);
SINGLY_LINKED_LIST* linked_list_reverse(SINGLY_LINKED_LIST*);

#endif
