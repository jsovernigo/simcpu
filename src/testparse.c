
#include "parse.h"
#include "queue.h"
#include "processes.h"
#include <stdio.h>

void print(void* v)
{
	int i;
	struct thread* t;

	t = (struct thread*) v;

	printf("\tProcess ID: %d\n\tThread ID: %d\n\tArrival Time: %d\n", t->pid, t->tid, t->atime);
	for(i = 0; i < t->burstc; i++)
	{
		printf("\t\tCPU Time: %d, IO Time: %d\n", t->bursts[i]->cputime, t->bursts[i]->iotime);
	}
	return;
}

int compare(void* v1, void* v2)
{
	struct thread* t1;
	struct thread* t2;

	t1 = (struct thread*) v1;
	t2 = (struct thread*) v2;

	return t2->atime - t1->atime;
}

int main()
{
	int i;
	int ts;
	int pdelay;
	int tdelay;
	struct thread** threads;
	struct queue* threadqueue;

	threadqueue = makeQueue();

	threads = readFile(&ts, &pdelay, &tdelay);
	if(threads == NULL)
	{
		return 1;
	}

	for(i = 0; i < ts; i++)
	{
		sortput(threadqueue, (void*) threads[i], &compare);
	}

	printqueue(threadqueue, &print);

	return 0;
}
