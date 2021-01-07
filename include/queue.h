#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

typedef struct _data {
    void * data;
    struct _data * next;
}data;

typedef struct _queue {
    size_t size;
    data* head;
    data* tail;
}queue;

/*
Create and return an empty queue
*/
queue* createQueue();
/*
Insert data into the queue(last position)
*/
void enqueue(queue * q, void* data);
/*
Remove first element of the queue of save its value to the toRet argument
*/
void* dequeue(queue * q);
/*
Save first element of the queue to the toRet argument
*/
void front(queue* q, void* toRet);//Return the first element
/*
Deletes all data of the queue
*/
void clearQueue(queue* q);
/*
Clears and destoys the queue
*/
void destroyQueue(queue* q);
/*
Return size of the queue
*/
size_t getSize(queue* q);
/*
Check is queue is empty
*/
boolean isEmpty(queue * q);


#endif