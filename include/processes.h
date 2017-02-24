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

struct process
{
	int pid;
	int threadc;

	struct thread** threads;
};

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

/**
 *
 */
struct process* makeProcess(int pid, int threadc, struct thread** threads);

/**
 *
 */
struct thread* makeThread(int pid, int tid, int burstc, int atime, struct burst** bursts);

/**
 *
 */
struct burst* makeBurst(int bid, int iotime, int cputime);

#endif
