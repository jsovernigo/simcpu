/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 */

#ifndef __GSOVERNIGO_EXEC_H__
#define __GSOVERNIGP_EXEC_H__

#include "queue.h"

/**
 *	exec
 *	executes the future events queue passed in, utilizing the flags passed in.
 *	IN:			fevents			- a queue of future events to arrive at the scheduler.
 *				detailed		- the detailed flag.  set to 1 to enable detailed output.
 *				verbose			- the verbose flag.  set to 1 to enable verbose output
 *				roundrobin		- set to 1 to enable round-robin scheduling
 *				quantum			- the quantum amount of time that will be allocated.
 *				pdelay			- the process-switch delay
 *				tdelay			- the thread-switch delay
 *	OUT:		returns the total execution time.
 *	POST:		prints events to the screen, fevents gets emptied.
 *	ERROR:		fevents is null, malloc fails.
 */
int exec(struct queue* fevents, int detailed, int verbose, int roundrobin, int quantum, int pdelay, int tdelay);

#endif
