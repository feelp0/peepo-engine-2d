#ifndef LIST_H
#define LIST_H
#include "common.h"

struct list_node {
    void* __data;
    struct list_node* __next;
    struct list_node* __previous;
};
typedef struct list_node list_node;

typedef struct {
    list_node* __head;
    list_node* __tail;
    uint __count;
} list;

list* list_new();
void list_destroy(list* list);
void list_add(list* list, void* elem);
boolean list_empty(list* list);
uint list_count(list* list);
void* list_item_at(list* list, uint index);
void list_add_at(list* list, void* elem, uint index);
void list_remove(list* list, void* elem);
void list_remove_at(list* list, uint index);
boolean list_contains(list* list, void* elem);

#endif