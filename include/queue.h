/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 *
 *	This file contains source for a queue ADT.
 */
#ifndef __GSOVERNIGO_QUEUE_H__
#define __GSOVERNIGO_QUEUE_H__

struct node;

struct queue;

/**
 *
 */
struct queue* makeQueue();

/**
 *
 */
struct node* makeNode(void* info);

/**
 *
 */
void destroyQueue(struct queue* queue, void (*destroy)(void*));

/**
 *
 */
struct node* getHead(struct queue* queue);

/**
 *
 */
void* getData(struct node* node);

/**
 *
 */
struct node* getNext(struct node* node);

/**
 *
 */
int put(struct queue* queue, void* info);

/**
 *
 */
int sortput(struct queue* queue, void* info, int (*comp)(void*, void*));

/**
 *
 */
void* get(struct queue* queue);

/**
 *
 */
void printqueue(struct queue* queue, void (*print)(void*));

#endif
