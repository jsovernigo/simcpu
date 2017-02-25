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


struct thread** readFile(int* nRead, int* processdelay, int* threaddelay)
{
	int i;
	int pNum;
	int pdelay;
	int tdelay;
	int threads;
	int cthread;

	char buffer[128];
	struct thread** tread;

	fgets(buffer, 128, stdin);
	sscanf(buffer ,"%d %d %d", &pNum, &pdelay, &tdelay);

	*processdelay = pdelay;
	*threaddelay = tdelay;

	threads = 0;
	cthread = 0;

	tread = malloc(sizeof(struct thread));
	
	/* repeat for every process outlined above */
	for(i = 0; i < pNum; i++)
	{
		int j;
		int pid;
		int threadc;

		/* capture pid and thread count for this process. */
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%d %d", &pid, &threadc);
		threads += threadc;

		tread = realloc(tread, sizeof(struct thread) * threads);

		/* for every thread in this process */
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

				iotime = 0;
				cputime = 0;
				bid = 0;

				struct burst* cb;

				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d %d %d", &bid, &cputime, &iotime);

				cb = makeBurst(bid, iotime, cputime);
				bread[k] = cb;
			}

			ct = makeThread(pid, tid, burstc, atime, bread);
			tread[cthread] = ct;
			cthread ++;
		}
	}

	*nRead = threads;

	return tread;
}
