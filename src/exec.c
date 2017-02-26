/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 */

#include "exec.h"
#include "processes.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int exec(struct queue* fevents, int detailed, int verbose, int roundrobin, int quantum, int pdelay, int tdelay)
{
	int ctime;

	int i;

	int numExec;
	int totTurn;
	int cputime;
	int iotime;
	int swapTime;
	int exectime;

	numExec = 0;
	totTurn = 0;
	ctime = 0;
	swapTime = 0;
	exectime = 0;

	cputime = 0;
	iotime = 0;

	struct queue* cpuqueue;
	struct queue* cevents;
	struct thread* loaded;
	struct cthread* finishedThread;
	struct cthread* temp;

	cpuqueue = makeQueue();
	cevents = makeQueue();
	loaded = NULL;

	if(roundrobin)
	{
		puts("RR\n");
	}
	else
	{
		puts("FCFS\n");
	}

	while(1)
	{
		/* if an new thread has just arrived */
		while(getHead(fevents) != NULL && ((struct thread*)getData(getHead(fevents)))->atime == ctime)
		{
			void* nthread;
			struct thread* nt;

			nthread = get(fevents);
			nt = (struct thread*) nthread;

			if(verbose)
			{
				printf("At System Time %d, Thread %d of Process %d changed from new to ready.\n", ctime, nt->tid, nt->pid);
			}

			put(cpuqueue, nthread);
		}

		/* load a new thread */
		if((loaded == NULL || threadDone(loaded)) && getHead(cpuqueue) != NULL)
		{
			if(loaded == NULL)
			{
				swapTime = pdelay + tdelay;
			}
			else if(loaded->pid != ((struct thread*) getData(getHead(cpuqueue)))->pid)
			{
				swapTime = pdelay + tdelay;
			}
			else if(loaded->tid != ((struct thread*) getData(getHead(cpuqueue)))->tid)
			{
				swapTime = tdelay;
			}

			/* free loaded */

			loaded = (struct thread*) get(cpuqueue);
			if(verbose)
			{
				printf("At System Time %d, Thread %d of Process %d changed from ready to running.\n", ctime, loaded->tid, loaded->pid);
			}


			if(roundrobin)
			{
				struct node* n;
				exectime = quantum;

				finishedThread = NULL;

				n = getHead(cevents);
				while(n != NULL)
				{
					struct cthread* switchto;

					switchto = (struct cthread*) getData(n);

					if(switchto->ct->tid == loaded->tid && switchto->ct->pid == loaded->pid)
					{
						finishedThread = switchto;
						break;
					}

					n = getNext(n);
				}
				/* check if no change */
				if(finishedThread == NULL)
				{
					finishedThread = makeCThread(loaded, 0, 0, 0, 0);
					put(cevents, (void*) finishedThread);
				}	
			}
			else
			{
				finishedThread = makeCThread(loaded, 0, 0, 0, 0);
				put(cevents, (void*) finishedThread);
			}
		}
		/* execute small amount of process. */
		else
		{
			int i;

			if(swapTime <= 0)
			{
				for(i = 0; i < loaded->burstc; i++)
				{
					if(!burstDone(loaded->bursts[i]))
					{
						if(loaded->bursts[i]->cputime == 0)
						{
							loaded->bursts[i]->iotime --;
							finishedThread->stime ++;
							finishedThread->iotime ++;
							iotime ++;
						}
						else
						{
							loaded->bursts[i]->cputime --;
							finishedThread->stime ++;
							cputime ++;
						}
						break;
					}
				}
				if(roundrobin)
				{
					exectime --;
					if(exectime == 0)
					{
						struct node* n;

						if(verbose)
						{
							printf("At System Time %d, Thread %d of Process %d changed from running to blocked.\n", ctime, loaded->tid, loaded->pid);
						}
						put(cpuqueue, (void*) loaded);

						if(verbose)
						{
							printf("At System Time %d, Thread %d of Process %d changed from blocked to ready.\n", ctime, loaded->tid, loaded->pid);
							printf("At System Time %d, Thread %d of Process %d changed from ready to running.\n", ctime, loaded->tid, loaded->pid);
						}

						loaded = (struct thread*) get(cpuqueue);

						n = getHead(cevents);

						finishedThread = NULL;
						while(n != NULL)
						{
							struct cthread* switchto;

							switchto = (struct cthread*) getData(n);

							if(switchto->ct->tid == loaded->tid && switchto->ct->pid == loaded->pid)
							{
								finishedThread = switchto;
								break;
							}

							n = getNext(n);
						}							

						/* check if no change */
						if(finishedThread == NULL)
						{
							finishedThread = makeCThread(loaded, 0, 0, 0, 0);
							put(cevents, (void*) finishedThread);
						}
					}
				}
			}
			else
			{
				swapTime --;
			}

			if(loaded != NULL && threadDone(loaded))
			{	
				numExec ++;
				totTurn += (ctime - loaded->atime);

				finishedThread->ttime = (ctime - loaded->atime);
				finishedThread->endtime = ctime;

				/* put(cevents, (void*) finishedThread); */

				if(verbose)
				{
					printf("At System Time %d, Thread %d of Process %d changed from running to terminated.\n", ctime, loaded->tid, loaded->pid);
				}
			}
		}

		if(getHead(cpuqueue) == NULL && getHead(fevents) == NULL && (loaded == NULL || threadDone(loaded)))
		{
			break;
		}

		ctime++;
	}

	printf("\nTotal time requied: %d\nAverage Turnaround time is: %.2lf\nCPU Utilization: %2d%%\n\n", ctime, ((float)totTurn)/numExec, ((iotime + cputime) * 100)/ctime);

	temp = (struct cthread*) get(cevents);

	while(temp != NULL)
	{
		if(detailed)
		{
			printf("Thread %d of Process %d:\n\nArrival Time: %d\nService Time: %d\nI/O Time: %d\nTurnaround Time: %d\nFinish Time: %d\n\n", temp->ct->tid, temp->ct->pid, temp->ct->atime, temp->stime, temp->iotime, temp->ttime, temp->endtime);
		}

		/* free everything. */
		for(i = 0; i < temp->ct->burstc; i++)
		{
			free(temp->ct->bursts[i]);
		}
		free(temp->ct->bursts);
		free(temp->ct);
		free(temp);

		temp = (struct cthread*) get(cevents);
	}

	destroyQueue(fevents, NULL);
	destroyQueue(cevents, NULL);
	destroyQueue(cpuqueue, NULL);

	/* essentially, return the total time run. */
	return ctime;
}
