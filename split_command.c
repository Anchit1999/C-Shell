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

char **split_command(char * cmd,char * DLM)
{
	char ** cmds = malloc(100 * (sizeof(char *)));
	char *cm;
	int p = 0;
	cm = strtok(cmd,DLM);
	while(cm!=NULL)
	{
		if(cm[0]=='\"')
			qt++;
		if(cm[0]=='|')
			pp++;
		cmds[p++] = cm;
		cm = strtok(NULL,DLM);
	}
	cmds[p]=NULL;
	return cmds;
}