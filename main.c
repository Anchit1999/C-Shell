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
#include<signal.h>
#include "Shellheader.h"

int argc;
void handle_sigint(int sig)
{
	printf("\n");
	// shell_prompt();
	// fflush(stdout);
	// printf("getpid:%d myCHILDpid:%d\n",getpid(),myMAINpid);
	if(getpid() != myMAINpid)
		return;
	// printf("%d\n",myCHILDpid);
	if(myCHILDpid != -1)
	{
		Run=0;
		// printf("hi i am here\n");
		kill(myCHILDpid, sig);
	}
	// signal(sig, handle_sigint);	
}

int main()
{
	root = getenv("PWD");
	myMAINpid = getpid();
	// printf("%s\n",root);
	signal(SIGINT, handle_sigint);
	signal(SIGTSTP, handle_sigint);
	while(1)
	{
		argc=0;
		myCHILDpid=-1;
		char *cmd = malloc(1024);
		shell_prompt();
		cmd = commands();
		// printf("%s\n",cmd);
		char **SCcmd;
		SCcmd = split_command(cmd,";");
		while(SCcmd[argc]!=NULL) argc++;
		// printf("%d\n",argc );
		for (int i = 0; i<argc ; i++)
		{
			char **cmds;
			char *sccmd = malloc(1024);
			strcpy(sccmd,SCcmd[i]);
			// printf("%s\n",SCcmd[i]);
			pp=0;
			for(int j=0;SCcmd[i][j]!='\0';j++)
			{
				if(SCcmd[i][j]=='|')
					pp++;
			}
			// printf("%d\n",pp);
			qt=0;
			if(pp)
			{
				my_pipe(SCcmd[i]);
			}
			else
			{
				// printf("%d eljcfmjfcv\n",pp);
				cmds = split_command(SCcmd[i]," \t\r\n\v\f\a");
				if(cmds[0]!=NULL && strcmp(cmds[0],"echo")==0 && qt)
				{
					cmds = NULL;
					cmds = split_command(sccmd,"\"");
					strcpy(cmds[0],"echo");
				}
				if(cmds[0]!=NULL)
				{
					// int j=0;
					// while(cmds[j]!=NULL)
					// {
					// 	printf("%s\n",cmds[j]);
					// 	j++;
					// }
					if(strcmp(cmds[0],"exit")==0 || strcmp(cmds[0],"quit")==0)
					{
						my_overkill();
						return EXIT_SUCCESS;
					}
					execute_cmd(cmds);
				}
			}
			free(cmds);
			free(sccmd);
		}
		pid_t wait_pid;
		int state;
		// printf("%d\n",fgpid );
		// printf("%d\n",getpid() );
		while((wait_pid = waitpid(-1,&state,WNOHANG))>0)
		{
			if(WIFEXITED(state) || WIFSIGNALED(state))
			{
				if(bgexit[wait_pid]!=NULL)
				{
					printf("%s with pid %d exited normally\n",bgexit[wait_pid],wait_pid);
					free(bgexit[wait_pid]);
					bgexit[wait_pid]=NULL;
				}
			}
		}
		// wait_pid = waitpid(-1,&state,WNOHANG);
		// printf("wait_pid: %lld\n",(ll)wait_pid);
		// printf("WIFEXITED: %lld\n",(ll)WIFEXITED(state) );
		// printf("WEXITSTATUS: %lld\n",(ll)WEXITSTATUS(state) );
		// if(!WIFEXITED(state))
		// 	printf("Process with pid %d exited normally\n",(int)ppid);

		free(cmd);
		// free(cmds);

	}
	return 0;
}