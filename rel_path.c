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

char* rel_path(char * cwd)
{
	int s_cwd = strlen(cwd),s_root = strlen(root);
	// printf("%d %d\n",s_cwd,s_root );
	if(s_root == s_cwd)
	{
		return "~";
	}
	else if(s_root > s_cwd)
	{
		return cwd;
	}
	else
	{
		char *CWD = (char*)malloc(100);
		for(int i=0;i<s_root;i++)
		{
			if(root[i]!=cwd[i])
				return cwd;
		}
		int i;
		CWD[0]='~';CWD[1]='/';
		for(i=s_root+1;i<s_cwd;i++)
		{
			CWD[2+i-(s_root+1)] = cwd[i];
		}
		CWD[2+i-(s_root+1)]='\0';
		return CWD;
	}
}