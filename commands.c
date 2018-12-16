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

char * commands()
{
	int i;
	char *cmd = (char*)malloc(100);
	// shell_prompt();
	for(i=0;;i++)
	{
		char s = getchar();
		if(s=='\n')
		{
			cmd[i]='\0';
			return cmd;
		}
		// printf("%c",s);
		cmd[i]=s;
	}
}