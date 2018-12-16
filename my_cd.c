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

// char prev_path[1000];
// char prev_path1[1000];
// int prev=0;
// prev_path = NULL;
void my_cd(char **args,int bg)
{
	// printf("%s\n",prev_path);
	if((args[1] == NULL || strcmp(args[1],"~")==0) && bg==0)
	{
		// prev=1;
		// getcwd(prev_path,1000);
		// printf("%d %s\n",(int)strlen(prev_path),prev_path);
		chdir(root);
	}
	// else if(strcmp(args[1],"-")==0 && bg==0)
	// {
	// 	if(prev)
	// 	{
	// 		strncpy(prev_path1,prev_path,strlen(prev_path));
	// 		getcwd(prev_path,1000);
	// 		printf("%s\n",prev_path1);
	// 		chdir(prev_path1);
	// 	}
	// 	else
	// 	{
	// 		printf("bash: cd: OLDPWD not set\n");
	// 	}
	// }
	else if(bg)
	{
			// printf("	cd background\n");
		pid_t pid;
		pid = fork();
		if(pid==0)
		{
			if(chdir(args[1]) !=0 && args[1]!=NULL)
			{
					// perror("bash");
				printf("bash: cd: %s: No such file or directory\n",args[1]);
			}
			exit(0);
		}
		else
		{
			printf("%lld\n",(ll)pid);
			bgexit[pid] = malloc(1000);
			strcpy(bgexit[pid],args[0]);
		}
	}
	else 
	{

		// getcwd(prev_path,1000);
		// printf("%d %s\n",(int)strlen(prev_path),prev_path);
		// strncpy(prev_path,args[1],sizeof(args[1]));
		// printf("%s\n",prev_path);
		int a = chdir(args[1]);
		if(a!=0)
			printf("bash: cd: %s: No such file or directory\n",args[1]);
		// else
		// {
		// 	if(prev==0)
		// 		prev=1;
		// }
	}
	// return;
}