/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 */

#include "processes.h"
#include "queue.h"
#include <stdio.h>

int fcfs(struct queue* fevents, int detailed, int verbose)
{
	int ctime;

	ctime = 0;

	struct queue* cpuqueue;
	struct thread* loaded;

	cpuqueue = makeQueue();
	loaded = NULL;

	while(1)
	{
		/* if an new thread has just arrived */
		if(getHead(fevents) != NULL)
		{
			if(((struct thread*)getData(getHead(fevents)))->atime == ctime)
			{
				void* nthread;
				struct thread* nt;

				nthread = get(fevents);
				nt = (struct thread*) nthread;

				if(verbose)
				{
					printf("Thread %d of Process %d arrived at the CPU at time %d.\n", nt->tid, nt->pid, ctime);
				}

				put(cpuqueue, nthread);
			}
		}

		ctime++;

		if(ctime == 100000)
		{
			break;
		}
	}

	/* essentially, return the total time run. */
	return ctime;
}
