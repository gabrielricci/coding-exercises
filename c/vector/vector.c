#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "types.h"

static void vector_check_size(vector* v) {
    if (v->size == 0) {
        v->size = 10;
        printf("Allocating %lu bytes\n", (sizeof(void*) * v->size));
        v->addr = malloc(sizeof(void*) * v->size);
        memset(v->addr, '\0', sizeof(void*) * v->size);
    }

    if (v->size == v->count) {
        v->size *= 2;
        v->addr = realloc(v->addr, sizeof(void*) * v->size);
    }
}

void vector_init(vector* v) {
    v->addr = NULL;
    v->size = 0;
    v->count = 0;
}

void vector_insert_at(vector* v, int pos, void* data) {
    vector_check_size(v);
    void** source_addr = v->addr + pos;
    void** dest_addr = source_addr + 1;

    memmove(dest_addr, source_addr, (v->size - pos) * sizeof(void*));
    *(v->addr + pos) = data;
}

void vector_push_back(vector* v, void* data) {
    vector_check_size(v);

    *(v->addr + v->count) = data;
    v->count++;
}

void vector_push_front(vector* v, void* data) {
    vector_insert_at(v, 0, data);
}

void* vector_value_at(vector* v, int pos) {
    return *(v->addr + pos);
}

void vector_free(vector* v){
    free(v->addr);
}

int vector_size(vector* v){
    return v->count;
}

int vector_empty(vector* v){
    if (v->count == 0) {
        return 1;
    }

    return 0;
}

void* vector_delete_at(vector* v, int pos) {
    void* data = vector_value_at(v, pos);
    void** dest_addr = v->addr + pos;
    void** source_addr = dest_addr + 1;

    memmove(dest_addr, source_addr, (v->size - pos - 1) * sizeof(void*));
    return data;
}

void* vector_pop(vector* v) {
    return vector_delete_at(v, (v->count - 1));
}

int main() {
    vector v;

    vector_init(&v);
    vector_push_back(&v, "this is the first item");
    vector_push_back(&v, "this is the second item");
    vector_push_back(&v, "this is the third item");

    printf("String = %s, Addr: %p\n", vector_value_at(&v, 0), &((&v)->addr[0]));
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 1), &((&v)->addr[1]));
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 2), &((&v)->addr[2]));
    printf("Size = %i\n", vector_size(&v));

    vector_push_back(&v, "this is the fourth item");
    vector_push_front(&v, "this is the new first item");

    printf("String = %s, Addr: %p\n", vector_value_at(&v, 0), &((&v)->addr[0]));
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 1), &((&v)->addr[1]));
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 2), &((&v)->addr[2]));
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 3), &((&v)->addr[3]));
    printf("Size = %i\n", vector_size(&v));

    vector_delete_at(&v, 2);
    vector_pop(&v);
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 0), &((&v)->addr[0]));
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 1), &((&v)->addr[1]));
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 2), &((&v)->addr[2]));
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 3), &((&v)->addr[3]));
    printf("String = %s, Addr: %p\n", vector_value_at(&v, 4), &((&v)->addr[4]));
    printf("Size = %i\n", vector_size(&v));

    vector_free(&v);

    return 0;
}
