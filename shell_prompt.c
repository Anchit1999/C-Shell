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

#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define GREEN "\033[0;32m"
#define BLUE "\033[1;34m"
#define MAG "\033[1;35m"

void shell_prompt()
{
	char hostname[1000];
	gethostname(hostname,1000);
	char* user = getenv("USER");
	char cwd[1000]; 
	getcwd(cwd,1000);
	char *CWD = rel_path(cwd);
	printf("%s<%s@%s:%s%s>%s",GREEN,user,hostname,CYAN,CWD,RESET);
	return;	
}