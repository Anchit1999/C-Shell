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

void my_setenv (char **args) 
{
	if (args[2] == NULL || args[3]!=NULL)
		perror("setenv");
	else if (setenv(args[1],args[2],1) != 0) perror("setenv");
	return ;	
}

void my_unsetenv (char **args) 
{
	if (unsetenv(args[1]) != 0) perror("unsetenv");
	return ;
}