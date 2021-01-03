#ifndef VECTOR_H
#define VECTOR_H
#include "common.h"

typedef struct {
    void** __items;
    uint __count;
    uint __capacity;
} vector;

vector* vector_new();
vector* vector_new_with_cap(uint cap);
void vector_add(vector* vec, void* elem);
void vector_add_at(vector* vec, void* elem, uint index);
void* vector_remove_at(vector* vec, uint index);
void* vector_remove(vector* vec, void* item);
uint vector_size(vector* vec);
vector* vector_resize(vector* vec, uint size);
void* vector_at(vector* vec, uint index);
void vector_foreach(vector* vec, void (*action)(void* p));
void vector_destroy(vector* vec);

void vector_quick(vector* vector, int (*comparator)(void*,void*));

#endif