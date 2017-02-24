/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 *
 *	This file contains source for a queue ADT.
 */
#include "queue.h"

#include <stdlib.h>

struct node
{
	void* data;
	struct node* next;
};

struct queue
{
	struct node* head;
};

struct queue* makeQueue()
{
	struct queue* q;

	q = malloc(sizeof(struct queue));
	if(q == NULL)
	{
		return NULL;
	}

	q->head = NULL;

	return q;
}

struct node* makeNode(void* info)
{
	struct node* node;

	node = malloc(sizeof(struct node));
	if(node == NULL)
	{
		return NULL;
	}

	node->data = info;
	node->next = NULL;

	return node;
}

void destroyQueue(struct queue* queue, void (*destroy)(void*))
{
	struct node* current;
	struct node* next;

	if(queue == NULL)
	{
		return;
	}
	else if(getHead(queue) == NULL)
	{
		free(queue);
		return;
	}

	current = getHead(queue);

	while(current != NULL)
	{
		next = current->next;
		if(destroy == NULL)
		{
			free(current->data);
		}
		else
		{
			destroy(current->data);
		}

		free(current);

		current = next;
	}

	free(queue);
}

struct node* getHead(struct queue* queue)
{
	if(queue == NULL)
	{
		return NULL;
	}
	else if(queue->head == NULL)
	{
		return NULL;
	}

	return queue->head;
}

void* getData(struct node* node)
{
	if(node == NULL)
	{
		return NULL;
	}
	else if(node->data == NULL)
	{
		return NULL;
	}

	return node->data;
}

struct node* getNext(struct node* node)
{
	if(node == NULL)
	{
		return NULL;
	}
	
	return node->next;
}

int put(struct queue* queue, void* info)
{
	struct node* cnode;
	struct node* nnode;

	if(queue == NULL)
	{
		return -1;
	}
	else if(queue->head == NULL)
	{
		nnode = makeNode(info);
		if(nnode == NULL)
		{
			return -1;
		}

		queue->head = nnode;
		return 0;
	}

	cnode = queue->head;

	while(getNext(cnode) != NULL)
	{
		cnode = getNext(cnode);
	}

	nnode = makeNode(info);
	if(nnode == NULL)
	{
		return -1;
	}
	cnode->next = nnode;

	return 0;
}

void* get(struct queue* queue)
{
	void* data;
	struct node* temp;

	if(queue == NULL)
	{
		return NULL;
	}
	else if(queue->head == NULL)
	{
		return NULL;
	}

	temp = queue->head;
	queue->head = queue->head->next;

	data = getData(temp);
	free(temp);

	return data;
}
