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

void execute_cmd(char **args)
{
	// printf("%s\n",args[0]);
	Run=1;
	int i,j,bg=0,rdt=0,Count=0;
	while(args[Count]!=NULL) Count++;
	// printf("Count %d\n",Count);
	for(i=0;i<Count;i++)
	{
		if(args[i]!=NULL && strcmp(args[i],"&")==0)
		{
			bg=1;
			args[i]=NULL;
		}
		else if(args[i]!=NULL)
		{
			for(j=0;args[i][j]!='\0';j++)
			{
				if(args[i][j]=='&')
				{
					bg=1;
					args[i][j]='\0';
				}
			}
		}
	}
	//BONUS REMINDME
	if(strcmp(args[0],"remindme")==0)
	{
		my_remindme(args);
	}
	else if(strcmp(args[0],"cd")==0)
	{
		my_cd(args,bg);
	}
	else if(strcmp(args[0],"pinfo")==0)
	{
		my_pinfo(args);
	}
	else if(strcmp(args[0],"setenv")==0)
	{
		my_setenv(args);
	}
	else if(strcmp(args[0],"unsetenv")==0)
	{
		my_unsetenv(args);
	}
	else if(strcmp(args[0],"kjob")==0)
	{
		my_kjob(args);
	}
	else if(strcmp(args[0],"fg")==0)
	{
		my_fg(args);
	}
	else if(strcmp(args[0],"bg")==0)
	{
		my_bg(args);
	}
	else if(strcmp(args[0],"overkill")==0)
	{
		my_overkill();
	}
	else
	{
		pid_t pid,wait_pid;
		int state;
		pid = fork();
		myCHILDpid = pid;
		if(pid==0)
		{
			if(bg) setpgid(0,0);
			my_redirect(args);
			if(strcmp(args[0],"clock")==0)
			{
				if(args[1]==NULL || strcmp(args[1],"-t")!=0)
					printf("usage: clock [-t] [-n] <time>\n");
				else
				{
				// printf("CLOCK\n");
					char flagn[1000];
					if(args[2]!=NULL && args[2][0]!='-')
						printf("usage: clock [-t] [-n] <time>\n");
					else
					{
						strncpy(flagn,args[2]+1,strlen(args[2]));
				// printf("%s\n",flagn);

						int num,flag;
						flag = atoi(flagn);
						if(args[3]==NULL)
							printf("usage: clock [-t] [-n] <time>\n");
						else
						{
							num = atoi(args[3]);
							while(flag--)
							{
								signal(SIGINT, handle_sigint);
								my_clock();
								sleep(num);
							}
						}
					}
				}
			}
			else if(strcmp(args[0],"jobs")==0)
			{
				// printf("jobsssss\n");
				my_jobs(0);
			}
			else if(strcmp(args[0],"echo")==0)
			{
				my_echo(args);
			}
			else if(strcmp(args[0],"pwd")==0)
			{
				my_pwd(args);
			}
			else if(strcmp(args[0],"ls")==0)
			{
				my_ls(args);
			}
			else
			{
				// if(!(strcmp(args[0],"vim")==0 && bg || strcmp(args[0],"vi")==0 && bg))
				// {
					int a = execvp(args[0],args);
					// signal(SIGINT, handle_sigint);
					if(a==-1)
					{
						// printf("1 from here\n");
						printf("%s: command not found\n",args[0]);
					}
				// }

			}
			// else if(execvp(args[0],args)!=-1)
			exit(EXIT_FAILURE);
		}
		else if(!bg)
		{
			// printf("%d\n",pid);
			bgexit[pid] = malloc(1000);
			strcpy(bgexit[pid],args[0]);
			do {
				wait_pid = waitpid(pid,&state,WUNTRACED);
			} while (!WIFEXITED(state) && !WIFSIGNALED(state) && Run);
			// waitpid(-1,NULL,WUNTRACED);
			// if(bgexit[pid]!=NULL)
			// {
			// 	free(bgexit[pid]);
			// 	bgexit[pid]=NULL;
			// }
		}
		else if(bg)
		{
			// signal(SIGINT, handle_sigint);
			// signal(SIGTSTP, handle_sigint);
			printf("%lld %s\n",(ll)pid,args[0]);
			bgexit[pid] = malloc(1000);
			strcpy(bgexit[pid],args[0]);
		}
	}
	return;
}