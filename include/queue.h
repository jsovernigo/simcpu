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
 * 	makequeue
 * 	makes a queue adt
 * 	IN:			void
 * 	OUT:		a new queue
 * 	POST:		returns a queue
 * 	ERROR:		malloc fails.
 */
struct queue* makeQueue();

/**
 *	makeNode
 *	makes a new node for the queue, storing info in it.
 *	IN:			info		- the void pointer info to be stored.
 *	OUT:		returns a new node to be put into a queue
 *	POST:		returns a node
 *	ERROR:		info null malloc fails
 */
struct node* makeNode(void* info);

/**
 *	destroyqueue
 *	destroys a queue adt, freeing all memory according to destroy
 *	IN:			queue		- the queue to be destroyed.
 *				destroy		- the destruction function for all info.
 *							  if NULL, use free() instead.
 *	OUT:		void
 *	POST:		queue has been freed, along with all of its data
 *	ERROR:		queue is null
 */
void destroyQueue(struct queue* queue, void (*destroy)(void*));

/**
 *	getHead
 *	gets the head of the queue adt (yeah, I know what it sounds like.
 *	I was tired when I wrote this function, and I regret its naming deeply.
 *	IN:			queue		- the queue that will be checked
 *	OUT:		a node is returned from the head of the queue.
 *	POST:		node returned.
 *	ERROR:		queue null.
 */
struct node* getHead(struct queue* queue);

/**
 * 	getData
 * 	returns the data of a node.
 * 	IN:			node		- the node we wil be checking
 * 	OUT:		the data stored in node.
 * 	POST:		returns the data of a node.
 * 	ERROR:		node is null.
 */
void* getData(struct node* node);

/**
 *	getNext
 *	returns the next item, following our currently pointed to node.
 *	IN:			node		- the node to be checked.
 *	OUT:		node->next
 *	POST:		returns node's next.
 *	ERROR:		node is null.
 */
struct node* getNext(struct node* node);

/**
 *	put
 *	puts info into a node on the head of the queue.
 *	IN:			queue 		- the queue that we will put info in
 *				info		- the info pointer we will be putting
 *	OUT:		returns 0 on success
 *	POST:		info is put TO THE BACK OF THE LINE.
 *	ERROR:		queue null, info null.
 */
int put(struct queue* queue, void* info);

/**
 *	sortput
 *	puts info into the queue, but uses comp to compare the pointers first.
 *	IN:			queue		- the queue that we will put info in.
 *				info		- the info we will insert into the queue.
 *				comp		- the comparison function. follows strcmp
 *	OUT:		0 on success.
 *	POST:		info has been inserted (sortedly) into the queue.
 *	ERROR:		queue is null, comp is null.
 */
int sortput(struct queue* queue, void* info, int (*comp)(void*, void*));

/**
 *	get
 *	gets the head of the queue, returning the data.
 *	IN:			queue		- the queue that will be beheaded.
 *	OUT:		returns the data of the head of the queue
 *	POST:		removes the head of the queue, too.
 *	ERROR:		queue null.
 */
void* get(struct queue* queue);

/**
 *	printqueue
 *	prints a queue, using print to print it correctly.
 *	IN:			queue		- the queue we will be printing.
 *				print		- prints the queue's nodes' data.
 *	OUT:		void
 *	POST:		prints the queue to stdout.
 *	ERROR:		queue is null, print is null.
 */
void printqueue(struct queue* queue, void (*print)(void*));

#endif
