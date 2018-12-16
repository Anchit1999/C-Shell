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

void my_echo(char **args)
{
	for(int i=1;args[i]!=NULL;i++)
	{
		printf("%s ",args[i]);
	}
	printf("\n");
	return;
}