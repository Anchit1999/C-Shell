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

void my_pwd(char **args)
{
	char *pwd = (char*)malloc(1000*sizeof(char));
	getcwd(pwd,1000);
	printf("%s\n",pwd);
	free(pwd);
	return;
}