/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 *
 * 	This file contains source used to parse the files containing cpu information.
 */

#include "parse.h"
#include <stdio.h>
#include <stdlib.h>


struct process** readFile(int* nRead)
{
	int i;
	int pNum;
	int pdelay;
	int tdelay;

	char buffer[128];
	struct process** pread;

	fgets(buffer, 128, stdin);
	sscanf(buffer ,"%d %d %d", &pNum, &pdelay, &tdelay);
	*nRead = pNum;

	pread = malloc(sizeof(struct process) * pNum);
	if(pread == NULL)
	{
		return NULL;
	}

	for(i = 0; i < pNum; i++)
	{
		int j;
		int pid;
		int threadc;

		struct process* cp;
		struct thread** tread;

		fgets(buffer, 128, stdin);
		sscanf(buffer, "%d %d", &pid, &threadc);

		tread = malloc(sizeof(struct thread) * threadc);

		for(j = 0; j < threadc; j++)
		{
			int k;
			int tid;
			int atime;
			int burstc;

			struct thread* ct;
			struct burst** bread;

			fgets(buffer, 128, stdin);
			sscanf(buffer, "%d %d %d", &tid, &atime, &burstc);

			bread = malloc(sizeof(struct burst) * burstc);

			for(k = 0; k < burstc; k++)
			{
				int bid;
				int cputime;
				int iotime;

				struct burst* cb;

				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d %d %d", &bid, &cputime, &iotime);

				cb = makeBurst(bid, iotime, cputime);
				bread[k] = cb;
			}

			ct = makeThread(pid, tid, burstc, atime, bread);
			tread[j] = ct;
		}
		
		cp = makeProcess(pid, threadc, tread);
		pread[i] = cp;
	}

	return pread;
}
