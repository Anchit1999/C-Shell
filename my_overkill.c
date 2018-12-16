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

void my_overkill()
{
	for(int i=0;i<=40000;i++)
	{
		if(bgexit[i]!=NULL)
		{
			kill(i,9);
			free(bgexit[i]);
			bgexit[i]=NULL;
		}
	}
	return;
}