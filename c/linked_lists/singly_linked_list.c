#include <stdlib.h>
#include <stdio.h>
#include "singly_linked_list.h"

static NODE* linked_list_create_node(int data) {
    NODE *n = (NODE*) malloc(sizeof(NODE));
    n->next = NULL;
    n->data = data;
    return n;
}

SINGLY_LINKED_LIST* linked_list_create(int data) {
    SINGLY_LINKED_LIST *list = (SINGLY_LINKED_LIST*) malloc(sizeof(SINGLY_LINKED_LIST));
    NODE* n = linked_list_create_node(data);
    list->head = list->tail = n;
    return list;
}


void linked_list_push_back(SINGLY_LINKED_LIST* list, int data) {
    NODE *n = linked_list_create_node(data);
    list->tail->next = n;
    list->tail = n;
}

void linked_list_push_front(SINGLY_LINKED_LIST* list, int data) {
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    NODE *n = linked_list_create_node(data);
    n->next = list->head;
    list->head = n;
}

NODE* linked_list_pop_back(SINGLY_LINKED_LIST* list) {
    NODE* element;

    if (list->head == list->tail) {
        element = list->head;
        list->head = NULL;
        list->tail = NULL;
        return element;
    }

    NODE* new_tail = list->head;

    while (new_tail->next != list->tail) {
        new_tail = new_tail->next;
    }

    new_tail->next = NULL;
    element = list->tail;
    list->tail = new_tail;
    return element;
}

NODE* linked_list_pop_front(SINGLY_LINKED_LIST* list) {
    NODE* first = list->head;
    NODE* second = first->next;
    list->head = second;
    return first;
}

int linked_list_size(SINGLY_LINKED_LIST* list) {
    int size = 0;

    NODE* element = list->head;
    while (element != NULL) {
        printf("%d\n", element->data);
        size++;
        element = element->next;
    }

    return size;
}

int linked_list_empty(SINGLY_LINKED_LIST* list) {
    if (list->head == NULL) {
        return 1;
    }
    return 0;
}

NODE* linked_list_value_at(SINGLY_LINKED_LIST* list, int pos) {
    int i = 0;
    NODE* element = list->head;

    while (element != NULL) {
        if (i == pos) {
            return element;
        }
        element = element->next;
        i++;
    }

    return NULL;
}

static NODE* linked_list_reverse_from_node(NODE* previous_node, NODE* curr_node) {
    if (curr_node->next) {
        NODE* next = linked_list_reverse_from_node(curr_node, curr_node->next);
        curr_node->next = previous_node;
        return next;
    }

    curr_node->next = previous_node;
    return curr_node;
}

SINGLY_LINKED_LIST* linked_list_reverse(SINGLY_LINKED_LIST* list) {
    NODE* new_tail = list->head;
    list->head = linked_list_reverse_from_node(NULL, list->head);
    list->tail = new_tail;
    return list;
}

int main() {
    SINGLY_LINKED_LIST* list = linked_list_create(10);

    linked_list_push_back(list, 11);
    linked_list_push_back(list, 12);
    linked_list_push_back(list, 13);
    linked_list_push_back(list, 14);
    linked_list_push_back(list, 15);

    printf("Head: %d\n", list->head->data);
    printf("Second: %d\n", list->head->next->data);
    printf("Third: %d\n", list->head->next->next->data);
    printf("Fourth: %d\n", list->head->next->next->next->data);
    printf("Fifth: %d\n", list->head->next->next->next->next->data);
    printf("Tail: %d\n", list->tail->data);

    linked_list_reverse(list);

    printf("At 0: %d\n", linked_list_value_at(list, 0)->data);
    printf("At 1: %d\n", linked_list_value_at(list, 1)->data);
    printf("At 2: %d\n", linked_list_value_at(list, 2)->data);
    printf("At 3: %d\n", linked_list_value_at(list, 3)->data);
    printf("At 4: %d\n", linked_list_value_at(list, 4)->data);
    printf("At 5: %d\n", linked_list_value_at(list, 5)->data);

    NODE* removed = linked_list_pop_back(list);
    printf("Removed: %d\n", removed->data);
    printf("Tail: %d\n", list->tail->data);

    removed = linked_list_pop_front(list);
    printf("Removed: %d\n", removed->data);
    printf("HEAD: %d\n", list->head->data);

    printf("Size: %d\n", linked_list_size(list));
    linked_list_pop_back(list);
    printf("Size: %d\n", linked_list_size(list));
    linked_list_pop_back(list);
    printf("Size: %d\n", linked_list_size(list));
    linked_list_pop_back(list);
    printf("Size: %d\n", linked_list_size(list));
    printf("Tail: %d\n", list->tail->data);

    NODE* last_one = linked_list_pop_back(list);
    printf("HEAD: %p\n", list->head);
    printf("Tail: %p\n", list->tail);
    printf("Last removed: %d\n", last_one->data);
    printf("Empty?: %d\n", linked_list_empty(list));
}
