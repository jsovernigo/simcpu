
#include "parse.h"
#include "processes.h"
#include <stdio.h>

int main()
{
	int i;
	int ps;
	struct process** prs;

	prs = readFile(&ps);
	if(prs == NULL)
	{
		return 1;
	}

	for(i = 0; i < ps; i++)
	{
		int j;
		printf("Pid: %d\n", prs[i]->pid);

		for(j = 0; j < prs[i]->threadc; j++)
		{
			int k;
			printf("\tTid: %d, Arrival Time: %d\n", prs[i]->threads[j]->tid, prs[i]->threads[j]->atime);

			for(k = 0; k < prs[i]->threads[j]->burstc; k++)
			{
				printf("\t\tCPU time: %d, IO time: %d\n", prs[i]->threads[j]->bursts[k]->cputime, prs[i]->threads[j]->bursts[k]->iotime);
			}

		}

	}

	return 0;
}
