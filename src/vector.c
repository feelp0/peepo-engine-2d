#include "vector.h"

vector* vector_new(){
    return vector_new_with_cap(10);
}

vector* vector_new_with_cap(uint cap){
    vector* vec = (vector*)malloc(sizeof(vector)); 
    if(vec == NULL) return NULL;
    vec->__count = 0;
    vec->__capacity = cap;
    vec->__items = malloc(vec->__capacity  * sizeof(void*));
    if(vec->__items == NULL) return NULL;
    return vec;
}

vector* vector_resize(vector* vec, uint size){
    void* ptr = realloc(vec->__items, size * sizeof(void*));
    if(ptr == NULL) return NULL;
    vec->__items = ptr;
    vec->__capacity = size;
    return vec;
}

void vector_add(vector* vec, void* elem){
    if(vec->__count == vec->__capacity){
        vector_resize(vec, vec->__capacity * 2);
    }
    int curr_index = vec->__count;
    vec->__items[curr_index] = elem;

    vec->__count++;
}

void vector_foreach(vector* vec, void (*action)(void* param)){
    for (uint i = 0; i < vec->__count; i++)
    {
        action(vec->__items[i]);
    }
}

uint vector_size(vector* vec){
    return vec->__count;
}

void vector_add_at(vector* vec, void* elem, uint index){
    if(index >= vec->__count) return;
    vec->__count++;
    if(vec->__count > vec->__capacity){
        vec = vector_resize(vec, vec->__capacity * 2);
    }
    void* old;
    void* new = elem;
    for (uint i = 0; i < vec->__count; i++)
    {
        old = vec->__items[i];
        vec->__items[i] = new;
        new = old;
    }
}

void* vector_remove_at(vector* vec, uint index){
    if(index >= vec->__count) return NULL;
    void* removedItem = vec->__items[index];
    for (uint i = index; i < vec->__count - 1; i++)
    {
        vec->__items[i] = vec->__items[i+1];
    }
    vec->__count--;
    if(vec->__count < vec->__capacity / 2){
        vec = vector_resize(vec, vec->__capacity / 2);
    }
    return removedItem;
}

void* vector_at(vector* vec, uint index){
    if(index >= vec->__count) return NULL;
    return vec->__items[index];
}

void vector_destroy(vector* vec){
    vec->__count = 0;
    free(vec->__items);
    free(vec);
}