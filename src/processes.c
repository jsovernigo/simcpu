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

struct process* makeProcess(int pid, int threadc, struct thread** threads)
{
	struct process* newProcess;

	newProcess = malloc(sizeof(struct process));
	if(newProcess == NULL)
	{
		return NULL;
	}

	newProcess->pid = pid;
	newProcess->threadc = threadc;
	newProcess->threads = threads;

	return newProcess;
}

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
