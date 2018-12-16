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

void my_pinfo(char **args)
{
	char PROC[1000];
	strcpy(PROC,"/proc/");
	if(args[1]!=NULL) strcat(PROC,args[1]);
	else strcat(PROC,"self");

	char STAT[1000];
	strcpy(STAT,PROC);
	strcat(STAT,"/status");
	// printf("%s\n",STAT);
	FILE * Status=fopen(STAT,"r");
	int fd = open(STAT,O_RDONLY);
	if(fd<0)
	{
		printf("No such process exist.\n");
	}
	else
	{
		char aa[20],bb[20];
		fscanf(Status,"%s",aa);
		fscanf(Status,"%s",bb);
		printf("Name: %s\n",bb);
	// printf("%s: %s\n",aa,bb);
		fclose(Status);

		strcpy(STAT,PROC);
		strcat(STAT,"/stat");
		FILE * Stat= fopen(STAT,"r");

		ll PID,Mem;char V,a;char Name[20];
		fscanf(Stat,"%lld",&PID);
		fscanf(Stat,"%s",Name);
		fscanf(Stat,"%c",&V);
		fscanf(Stat,"%c",&a);
	// printf("a: %c\n",a);
		printf("Pid: %lld\n",PID);
		printf("Process Status: %c\n",a);
		fclose(Stat);

		strcpy(STAT,PROC);
		strcat(STAT,"/statm");
		FILE * Statm = fopen(STAT,"r");
		fscanf(Statm,"%lld",&Mem);
		printf("Virtual Memory: %lld KB\n",4*Mem);
		fclose(Statm);

		strcpy(STAT,PROC);
		strcat(STAT,"/exe");
		char exeP[1000];
		int cnt = readlink(STAT,exeP,sizeof(exeP));
		if(cnt > 0)
		{
			char *CWD = (char*)malloc(100);
			exeP[cnt]='\0';
			int s_root = strlen(root),s_exeP = strlen(exeP),flag=0;

			if(s_exeP>s_root)
			{
				for(int i=0;i<s_root;i++)
				{
					if(root[i]!=exeP[i])
					{
					// for replacing with ~
						flag=1;
						break;
					}
				}

				if(flag==0)
				{
					int i;
					CWD[0]='~';CWD[1]='/';
					for(i=s_root+1;i<s_exeP;i++)
					{
						CWD[2+i-(s_root+1)] = exeP[i];
					}
					CWD[2+i-(s_root+1)]='\0';
					printf("Exectuable Path: %s\n",CWD);
				}
				else
				{
					printf("Exectuable Path: %s\n",exeP);
				}
			}
			else
			{
				printf("Exectuable Path: %s\n",exeP);
			}
		}
		else
			perror("pinfo: ");
	}
}