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

void my_pipe(char *cmd)
{
	// printf("PIPE PIPE\n");
	Run=1;
	int k=0;
	// while(args[Count]!=NULL) Count++;
	int num_pipe=0;
	// printf("%s\n",cmd );
	// printf("111\n");
	char **cmds = split_command(cmd,"|");
	while(cmds[k]!=NULL)
	{
		// printf("%s\n",cmds[k]);
		k++;
	}
	cmds[k]=NULL;
	// printf("%d\n",k);
	int prev,next,mypipe[2];
	for(int i=0;i<k;i++)
	{
		int fd_in,fd_out,Count=0,bg=0;
		char **args = split_command(cmds[i]," \t\r\n\v\f\a");
		// printf("%s\n",args[0]);
		// printf("222\n");
		prev=next=1;
		if(i==0)
		{
			prev=0;
		}
		if(i==k-1)
		{
			next=0;
		}
		if(prev)
		{
			close(mypipe[1]);
			fd_in = dup(0);
			dup2(mypipe[0],0);
			close(mypipe[0]);
		}
		if(next)
		{
			if(pipe(mypipe) != 0) {
				perror("pipe failed");
			}
			fd_out = dup(1);
			dup2(mypipe[1],1);
		}
		while(args[Count]!=NULL)
		{
			// printf("%s ",args[Count]);
			// printf("Count %d\n",Count);
			Count++;
		}
		// printf("\n");
		for(int j=0;j<Count;j++)
		{
			if(args[j]!=NULL && strcmp(args[j],"&")==0)
			{
				bg=1;
				args[j]=NULL;
			}
			else if(args[j]!=NULL)
			{
				for(int l=0;args[j][l]!='\0';l++)
				{
					if(args[j][l]=='&')
					{
						bg=1;
						args[j][l]='\0';
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
			// printf("222\n");
			pid_t pid,wait_pid;
			int state;
			pid = fork();
			if(pid==0)
			{
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
									// signal(SIGINT, handle_clock);
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
					if(!(strcmp(args[0],"vim")==0 && bg || strcmp(args[0],"vi")==0 && bg))
					{
						// printf("%s\n",args[0]);
						int a = execvp(args[0],args);
						// signal(SIGINT, handle_clock);
						if(a==-1)
						{
							printf("2 From here\n");
							printf("%s: command not found\n",args[0]);
						}
					}

				}
			// else if(execvp(args[0],args)!=-1)
				exit(EXIT_FAILURE);
			}
			else if(!bg)
			{
				bgexit[pid] = malloc(1000);
				strcpy(bgexit[pid],args[0]);
				do {
					wait_pid = waitpid(pid,&state,WUNTRACED);
				} while (!WIFEXITED(state) && !WIFSIGNALED(state) && Run);
				dup2(fd_in,0);
				dup2(fd_out,1);
			}
			else if(bg)
			{
				printf("%lld\n",(ll)pid);
				bgexit[pid] = malloc(1000);
				strcpy(bgexit[pid],args[0]);
			}
		}
	}
	return;
}