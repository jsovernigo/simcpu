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

struct thread** readFile(int* nRead, int* pdelay, int* tdelay);

#endif
