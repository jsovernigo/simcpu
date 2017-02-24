
#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

#define TESTS 20

int* getIntPtr(int i)
{
	int* np;

	np = malloc(sizeof(int));
	*np = i;

	return np;
}

int main()
{
	int i;
	struct queue* queue;
	struct node* node;

	queue = makeQueue();

	for(i = 0; i < TESTS; i++)
	{
		put(queue, (void*) getIntPtr(i));
	}

	node = getHead(queue);

	for(i = 0; i < TESTS; i++)
	{
		void* ptr;

		ptr = get(queue);
		put(queue, ptr);

		node = getHead(queue);

		while(node != NULL)
		{
			printf("%2d ", *((int*) getData(node)));
			node = getNext(node);
		}
		printf("\n");
	}
	
	destroyQueue(queue, NULL);

	return 0;
}
