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

void* vector_remove(vector* vec, void* item){
    for (uint i = 0; i < vec->__count; i++)
    {
        void* i_item = vector_at(vec, i);
        if(i_item == item){
            void* v = vector_remove_at(vec, i);
            return v;
        }
    }
    return NULL;
}

void vector_clear(vector* vec){
    uint size = (int)vector_size(vec);
    if(size == 0) return;
    for (int i = size - 1; i >= 0; i--)
    {
        vector_remove_at(vec, i);
    }
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

void __vector_quick_recurs(vector* vector,int (*comparator)(void*,void*),uint start_index,uint end_index){
    if(start_index >= end_index) 
        return;  // se si incrociano ritorno 
    int pivot_index = __vector_quick_partition(vector, comparator, start_index, end_index); //nonostante gli indici so positivi, 
                                                                                                //accettiamo anche indici negativi per non bloccare la funzione dopo
    __vector_quick_recurs(vector, comparator, start_index, pivot_index-1);
    __vector_quick_recurs(vector, comparator, pivot_index +1 , end_index);

}

void vector_quick(vector* vector, int (*comparator)(void*,void*)){
    __vector_quick_recurs(vector, comparator, 0, vector->__count -1);
}


int __vector_quick_partition(vector* vector,int (*comparator)(void*,void*),uint start_index,uint end_index){

    int pivot_index = start_index; 
    int left_index = start_index;
    int right_index = end_index;

    void* item  = NULL;
    void* pivot = NULL;
    while( left_index<right_index){

        boolean itemIsGTE = true;
        while(itemIsGTE && pivot_index<right_index){

            item = vector_at(vector, right_index);
            pivot = vector_at(vector, pivot_index);
            itemIsGTE = comparator(item, pivot) != -1;
            if(itemIsGTE){
                right_index--;
            }
        }
        if(pivot_index != right_index){
            vector->__items[pivot_index] = item;
            vector->__items[right_index] = pivot;
            pivot_index = right_index;
        }

        boolean itemIsLTE = true;
        while(itemIsLTE && pivot_index > left_index){
            item = vector_at(vector,left_index);
            pivot = vector_at(vector, pivot_index);
            itemIsLTE = comparator(item, pivot) != 1;
            if(itemIsLTE){
                left_index++;
            }
        }
        if(pivot_index != left_index){
            vector->__items[pivot_index] = item;
            vector->__items[left_index] = pivot;
            pivot_index = left_index;
        }
    }
    return pivot_index;
}
