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

void my_remindme(char **args)
{
	int num;
	if(args[1]!=NULL)
		num = atoi(args[1]);
	if(args[1]==NULL || strcmp(args[1],"0")!=0 && num==0 || args[2]==NULL)
		printf("usage: remindme [n] [message]\n");
	// printf("%d\n",num);
	else
	{
		pid_t pid;
		pid = fork();
		if(pid==0)
		{
			sleep(num);
			printf("\n");
			for(int i=2;args[i]!=NULL;i++)
			{
				for(int j=0;args[i][j]!='\0';j++)
				{
					if(args[i][j]!='\"')
						printf("%c",args[i][j]);
				}
				printf(" ");
			}
			printf("\n");
		}
	}
	return;
}