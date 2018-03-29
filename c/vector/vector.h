#ifndef VECTOR_H__
#define VECTOR_H__

typedef struct vector_ {
    void** addr;
    int size;
    int count;
} vector;

void vector_init(vector*);
void vector_push_back(vector*, void*);
void vector_push_front(vector*, void*);
void* vector_value_at(vector*, int);
void vector_free(vector*);
int vector_size(vector*);
int vector_empty(vector*);
void insert_at(vector*, int, void*);
void* vector_pop(vector*);
void* vector_delete_at(vector*, int);

#endif
