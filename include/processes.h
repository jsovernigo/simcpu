/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 *
 * 	This file contains code and structs which can be used to contain processes
 * 	and their threading information.  Please note that the structure used is
 * 	declared here, but defined in the c file of the same name.
 */
#ifndef	__GSOVERNIGO_PROCESSES_H__
#define __GSOVERNIGO_PROCESSES_H__

struct thread
{
	int pid;
	int tid;
	int burstc;
	int atime;

	struct burst** bursts;	
};

struct burst
{
	int bid;
	int iotime;
	int cputime;
};

struct cthread
{
	struct thread* ct;
	int stime;
	int iotime;
	int ttime;
	int endtime;
};

/**
 *	makeThread
 *	makes a thread adt, returning it when done.
 *	IN:			pid			- the process id of this thread
 *				tid			- the thread id of this thread (local to thread)
 *				burstc		- the burst count for this thread.
 *				atime		- the thread arrival time.
 *				bursts		- a burst array.
 *	OUT:		returns the thread that was created.
 *	POST:		returns a thread adt.
 *	ERROR:		bursts is null.
 */
struct thread* makeThread(int pid, int tid, int burstc, int atime, struct burst** bursts);

/**
 *	makeBurst
 *	creates a burst adt, returning it when done.
 *	IN:			bid			- the burst id.
 *				iotime		- the iotime for this burst.
 *				cputime		- the cputime required for this cputime
 *	OUT:		returns a burst adt
 *	POST:		a burst has been returned
 *	ERROR:		malloc fails
 */
struct burst* makeBurst(int bid, int iotime, int cputime);

/**
 *	makeCThread
 *	creates a finished thread adt, and returns it
 *	IN:			endthread	- the ended thread.
 *				stime		- the service time
 *				iotime		- the io time done to this thread.
 *				ttime		- the turnaround time
 *				endtime		- the ending time of the thread
 *	OUT:		a completed thread adt
 *	POST:		returns a thread
 *	ERROR:		endthread is null.
 */
struct cthread* makeCThread(struct thread* endthread, int stime, int iotime, int ttime, int endtime);

/**
 * 	burstDone
 * 	checks if a burst is completed.
 * 	IN:			burst		- a burst adt to be checked.
 * 	OUT:		returns 1 if done, 0 if not completed.
 * 	POST:		returns int
 * 	ERROR:		burst is null.
 */
int burstDone(struct burst* burst);

/**
 *	threadDone
 *	checks if a thread is done (add bursts done)
 *	IN:			thread		- a thread to be checked.
 *	OUT:		1 if thread done, 0 if still requires time
 *	POST:		int returned
 *	ERROR:		thead null or any thread->burst null.
 */
int threadDone(struct thread* thread);

#endif
