/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 */
#include "queue.h"
#include "parse.h"
#include "processes.h"
#include "exec.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * 	print
 *	prints the thread passed in as void
 *	IN:			v			- a void pointer pointing to a thread adt 
 *	OUT:		void
 *	POST:		t has been printed to the screen
 *	ERROR:		v is NULL.
 */
void print(void* v)
{
	int i;
	struct thread* t;

	t = (struct thread*) v;

	printf("Process ID: %d\nThread ID: %d\nArrival Time: %d\n", t->pid, t->tid, t->atime);
	for(i = 0; i < t->burstc; i++)
	{
		printf("\tCPU Time: %d, IO Time: %d\n", t->bursts[i]->cputime, t->bursts[i]->iotime);
	}
	puts("-----------------------------------------------------");
	return;
}

/**
 *	compare
 *	compares two threads by arrival time
 *	IN:			v1			- thread 1
 *				v2			- thread 2
 *	OUT:		see strcmp's return. (v2time - v1time)
 *	POST:		int returned
 *	ERROR:		either null
 */
int compare(void* v1, void* v2)
{
	struct thread* t1;
	struct thread* t2;

	t1 = (struct thread*) v1;
	t2 = (struct thread*) v2;

	return t2->atime - t1->atime;
}

/**
 *	main
 *	main function, calls other functions.
 *	IN:			argc		- the argument count
 *				argv		- the argument vector
 *	OUT:		returns 0 on success.
 *	POST:		program has run
 *	ERROR:		see any other error in the program.
 */
int main(int argc, char** argv)
{
	int i;
	int threadc;
	int pdelay;
	int tdelay;

	int detailed;
	int verbose;
	int roundrobin;
	int quantum;

	struct thread** threads;
	struct queue* threadqueue;

	threadqueue = makeQueue();

	verbose = 0;
	detailed = 0;
	roundrobin = 0;
	quantum = 1;

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-d") == 0)
		{
			detailed = 1;
		}
		else if(strcmp(argv[i], "-v") == 0)
		{
			verbose = 1;
		}
		else if(strcmp(argv[i], "-r") == 0)
		{
			roundrobin = 1;
			if(i < argc - 1)
			{
				quantum = atoi(argv[i+1]);
				i++;
			}
			else
			{
				puts("Round Robin flag missing quantum time.");
				return 1;
			}
		}
	}

	threads = readFile(&threadc, &pdelay, &tdelay);
	if(threads == NULL)
	{
		free(threadqueue);
		return 1;
	}

	for(i = 0; i < threadc; i++)
	{
		sortput(threadqueue, (void*) threads[i], &compare);
	}
	free(threads);


	exec(threadqueue, detailed, verbose, roundrobin, quantum, pdelay, tdelay);

	return 0;
}
