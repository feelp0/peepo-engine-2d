#include "queue.h"
#include <string.h>

queue *createQueue()
{
	queue *q = (queue *)calloc(1, sizeof(queue));
	if (q == NULL)
	{
		return NULL;
	}

	q->size = 0;
	q->head = q->tail = NULL;
	return q;
}

void enqueue(queue *q, void *_data)
{
	if (q == NULL)
		printf("Enqueue Error: Queue can't be null");

	if (_data == NULL)
		printf("Enqueue Error: Data is NULL.");

	data *d = (data *)calloc(1, sizeof(data));
	d->data = _data;
	d->next = NULL;

	if (q->size == 0)
	{  //First insertion
		q->head = q->tail = d;
	}
	else
	{
		q->tail->next = d;
		q->tail = d;
	}

	q->size++;
}

void *dequeue(queue *q)
{
	if(q == NULL)
		printf("Dequeue Error: Queue is NULL");

	if(isEmpty(q))
		printf("Dequeue Error: Queue is empty");

	void *temp = q->head->data;
	if (q->size == 1)
	{
		//free(q->head);
		data* oldHead = q->head;
		q->head = q->tail = NULL;
		free(oldHead);
	}
	else
	{
		data* oldHead = q->head;
		//free(q->head);
		q->head = q->head->next;
		free(oldHead);
		//q->head = q->head->next;
	}

	q->size--;
	return temp;
}

void clearQueue(queue *q)
{
	if (q == NULL)
	{
		fprintf(stderr, "clear() Queue can't be null");
		exit(-1);
	}

	while (!isEmpty(q))
	{
		data *temp = q->head;
		q->head = q->head->next;
		free(temp);
		q->size--;
	}
}

size_t getSize(queue *q)
{
	if (q == NULL)
	{
		fprintf(stderr, "getSize() Queue can't be null");
		exit(-1);
	}

	return q->size;
}

boolean isEmpty(queue *q)
{
	if (q == NULL)
	{
		return true;
	}
	if (q->size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void destroyQueue(queue *q)
{
	clearQueue(q);
	free(q);
}