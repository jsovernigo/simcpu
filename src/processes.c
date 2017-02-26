/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 *
 * 	This file contains code and structs which can be used to contain processes
 * 	and their threading information.  Please note that the structure used is
 * 	declared here, but defined in the c file of the same name.
 */

#include "processes.h"
#include <stdlib.h>

struct thread* makeThread(int pid, int tid, int burstc, int atime, struct burst** bursts)
{
	struct thread* newThread;

	newThread = malloc(sizeof(struct thread));
	if(newThread == NULL)
	{
		return NULL;
	}

	newThread->pid = pid;
	newThread->tid = tid;
	newThread->burstc = burstc;
	newThread->atime = atime;
	newThread->bursts = bursts;

	return newThread;
}

struct burst* makeBurst(int bid, int iotime, int cputime)
{
	struct burst* newBurst;

	newBurst = malloc(sizeof(struct burst));
	if(newBurst == NULL)
	{
		return NULL;
	}

	newBurst->bid = bid;
	newBurst->iotime = iotime;
	newBurst->cputime = cputime;

	return newBurst;
}

struct cthread* makeCThread(struct thread* endthread, int stime, int iotime, int ttime, int endtime)
{
	struct cthread* finishedThread;

	finishedThread = malloc(sizeof(struct cthread));
	if(finishedThread == NULL)
	{
		return NULL;
	}

	finishedThread->ct = endthread;
	finishedThread->stime = stime;
	finishedThread->iotime = iotime;
	finishedThread->ttime = ttime;
	finishedThread->endtime = endtime;

	return finishedThread;
}

int burstDone(struct burst* burst)
{
	if(burst->iotime == 0 && burst->cputime == 0)
	{
		return 1;
	}
	return 0;
}

int threadDone(struct thread* thread)
{
	int i;

	for(i = 0; i < thread->burstc; i++)
	{
		if(!burstDone(thread->bursts[i]))
		{
			return 0;
		}
	}
	return 1;
}
