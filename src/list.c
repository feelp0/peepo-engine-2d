#include "list.h"
#include <stdlib.h> 

list* list_new(){
    list* l = (list*)malloc(sizeof(list));
    l->__head = NULL;
    l->__tail = NULL;
    l->__count = 0;
    return l;
}

void list_destroy(list* list){
    list_node* each = list->__head;
    while(each){
        list_node* next = each->__next;
        free(each);
        each = next;
    }
    free(list);
}

void list_add(list* list, void* elem){
    list_node* node = (list_node*)malloc(sizeof(list_node));
    node->__data = elem;
    node->__next = NULL;
    node->__previous = NULL;
    if(list->__head == NULL){
        list->__head = node;
        list->__tail = node;
    }
    else{
        node->__previous = list->__tail;
        list->__tail->__next = node;
        list->__tail = node;
    }
    list->__count++;
}

boolean list_empty(list* list){
    if(list->__head == NULL)
        return true;
    return false;
}

uint list_count(list* list){
    return list->__count;
}

void* list_item_at(list* list, uint index){
    if(index >= list->__count){
        return NULL;
    }

    list_node* elem = list->__head;
    for (uint i = 0; i < index; i++)
    {
        elem = elem->__next;
    }
    
    return elem->__data;
}

void list_add_at(list* list, void* elem, uint index){
    list_node* node = (list_node*)malloc(sizeof(list_node));
    node->__data = elem;
    node->__next = NULL;
    node->__previous = NULL;

    if(index >= list->__count){
        list_add(list, elem);
    }
    else if(index == 0){
        node->__next = list->__head;
        list->__head = node;
        list->__count++;
    }
    else{
        list_node* elem = list->__head;
        for (uint i = 0; i < index-1; i++)
        {
            elem = elem->__next;
        }
        elem->__next->__previous = node;
        elem->__next = node;
        list->__count++;
    }
}

void list_remove(list* list, void* elem){
    if(list->__head->__data == elem){
        list_remove_at(list, 0);
        return;
    }
    if(list->__tail->__data == elem){
        list_remove_at(list, list->__count-1);
        return;
    }
    list_node* node = list->__head->__next;
    while(node != NULL){
        if(node->__data == elem){
            node->__previous->__next = node->__next;
            node->__next->__previous = node->__previous;
            free(node);
            list->__count--;
            return;
        }
        node = node->__next;
    }
}

void list_remove_at(list* list, uint index){
    if(index >= list->__count) return;

    if(index == 0){
        list_node* old_head = list->__head;
        list->__head = list->__head->__next;
        list->__head->__previous = NULL;

        free(old_head);
        list->__count--;
        return;
    }
    else if(index == list->__count-1){
        list_node* old_tail = list->__tail;
        list->__tail = list->__tail->__previous;
        list->__tail->__next = NULL;

        free(old_tail);
        list->__count--;
        return;
    }
    else{
        list_node* elem = list->__head;
        for (uint i = 0; i < index; i++)
        {
            elem = elem->__next;
        }
        elem->__previous->__next = elem->__next;
        elem->__next->__previous = elem->__previous;
        free(elem);
        list->__count--;
        return;
    }
}

boolean list_contains(list* list, void* elem){
    list_node* item = list->__head;
    while(item != NULL){
        if(item->__data == elem){
            return true;
        }
        item = item->__next;
    }
    return false;
}