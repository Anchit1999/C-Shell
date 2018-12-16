#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include "Shellheader.h"

void my_kjob(char **args)
{
	if(args[1]==NULL || args[2]==NULL)
	{
		printf("Usage: kjob <jobnumber> <signalNumber>\n");
	}
	else
	{
		// printf("%d\n",atoi(args[1]));
		// printf("%d",my_jobs(atoi(args[1])));
		// my_jobs(1);
		int k=0;
		char STAT[1000];
		char pid[10];
		int fd1;
		for(int i=0;i<40000;i++)
		{
			if(bgexit[i]!=NULL)
			{
				strcpy(STAT,"/proc/");
				sprintf(pid,"%d",i);
				strcat(STAT,pid);
				strcat(STAT,"/status");
				// printf("%s\n",STAT);
				fd1 = open(STAT,O_RDONLY);
				if(fd1>=0)
				{
					k++;
				}
				close(fd1);
			}
			if(k==atoi(args[1]))
			{
				int kl = kill(i,atoi(args[2]));
				if(kl==-1)
					printf("kjob failed\n");
				else
				{
					free(bgexit[i]);
					bgexit[i]=NULL;
				}
				break;
			}
		}
		if(k!=atoi(args[1]))
		{
			printf("No such job exist.\n");
		}
	}
	return;
}