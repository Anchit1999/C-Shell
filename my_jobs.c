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


void my_jobs(int flag)
{
	char STAT[1000];
	char pid[10];
	int fd1,fd2,k=0;
	char name[100],extra[100];
	char S;
	int pidp;
	for(int i=0;i<40000;i++)
	{
		if(bgexit[i]!=NULL)
		{
			strcpy(STAT,"/proc/");
			sprintf(pid,"%d",i);
			strcat(STAT,pid);
			strcat(STAT,"/status");
			// printf("%s\n",STAT);
			FILE * Status=fopen(STAT,"r");
			fd1 = open(STAT,O_RDONLY);
			if(fd1>=0)
			{
				k++;
				fscanf(Status,"%s",name);
				fscanf(Status,"%s",name);
				fclose(Status);
			}
			else
			{
				free(bgexit[i]);
				bgexit[i]=NULL;
				close(fd1);
				continue;
			}
			close(fd1);

			strcpy(STAT,"/proc/");
			sprintf(pid,"%d",i);
			strcat(STAT,pid);
			strcat(STAT,"/stat");

			FILE * Stat = fopen(STAT,"r");
			fd1 = open(STAT,O_RDONLY);
			if(fd1>=0)
			{
				fscanf(Stat,"%d",&pidp);
				fscanf(Stat,"%s",extra);
				fscanf(Stat,"%s",extra);
				if(strcmp(extra,"S")==0 || strcmp(extra,"R")==0) strcpy(extra,"Running");
				if(strcmp(extra,"T")==0) strcpy(extra,"Stopped");
				// printf("%s\n",extra);
			}
			close(fd1);
			printf("[%d] %s %s %d\n",k,extra,name,pidp);
		}
	}
}