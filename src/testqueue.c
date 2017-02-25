
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

int compare(void* n1, void* n2)
{
	int i = *((int*)n1);
	int j = *((int*)n2);

	return j - i;
}

int main()
{
	int i;
	struct queue* queue;
	struct node* node;

	queue = makeQueue();

	for(i = 0; i < TESTS; i += 2)
	{
		sortput(queue, (void*) getIntPtr(i), &compare);
	}
	for(i = 1; i < TESTS; i+= 2)
	{
		sortput(queue, (void*) getIntPtr(i), &compare);
	}

	node = getHead(queue);

	while(node != NULL)
	{
		printf("%2d ", *((int*) getData(node)));
		node = getNext(node);
	}
	printf("\n");
	destroyQueue(queue, NULL);

	return 0;
}
