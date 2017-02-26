/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 *
 * 	This file contains source used to parse the files containing cpu information.
 */
#ifndef __GSOVERNIGO_PARSE_H__
#define __GSOVERNIGO_PARSE_H__

#include "processes.h"

/**
 *	readFile
 *	reads the file that is passed through stdin
 *	IN:			nRead			- the numer of items read.
 *				pdelay			- the process delay
 *				tdelay			- the thread delay
 *	OUT:		an array of threads.
 *	POST:		all passed in pointers are changed.
 *	ERROR:		any pointers passed in are null.
 */
struct thread** readFile(int* nRead, int* pdelay, int* tdelay);

#endif
