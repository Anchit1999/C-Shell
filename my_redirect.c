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

void my_redirect(char **args)
{
	int in=0,out=0,append=0,state,i=0,Count=0;
	char In[50],Out[50],Append[50];
	while(args[Count]!=NULL) Count++;
	// printf("Count %d\n",Count);
	for(i=0;i<Count;i++)
	{
		if(args[i]!=NULL && strcmp(args[i],">")==0)
		{
			out=1;
			strcpy(Out,args[i+1]);
			args[i]=NULL;
			args[i+1]=NULL;
		}
		if(args[i]!=NULL && strcmp(args[i],"<")==0)
		{
			in=1;
			strcpy(In,args[i+1]);
			args[i]=NULL;
			args[i+1]=NULL;
		}
		if(args[i]!=NULL && strcmp(args[i],">>")==0)
		{
			append=1;
			strcpy(Append,args[i+1]);
			args[i]=NULL;
			args[i+1]=NULL;
		}
	}
	if(in)
	{
		int fd = open(In,O_RDONLY);
		if(fd<0)
		{
			perror("No such file exist");
			exit(0);
		}
		dup2(fd,0);
		close(fd);
	}
	if(out)
	{
		int fd = open(Out,O_CREAT | O_WRONLY | O_TRUNC,00644);
		if(fd<0)
		{
			
			perror("Unable to open/create file");
			exit(0);
		}
		dup2(fd,1);
		close(fd);
	}
	if(append)
	{
		int fd = open(Append,O_CREAT | O_WRONLY | O_APPEND,00644);
		if(fd<0)
		{
			perror("Unable to open/create file");
			exit(0);
		}
		dup2(fd,1);
		close(fd);
	}
	return;
}