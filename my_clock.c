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

void my_clock()
{
	char clk[1000];
	strcpy(clk,"/sys/class/rtc/rtc0");

	char date[1000];
	strcpy(date,clk);
	strcat(date,"/date");
	FILE * dt=fopen(date,"r");
	char DT[20];
	fscanf(dt,"%s",DT);
	printf("%s ",DT );

	strcpy(date,clk);
	strcat(date,"/time");

	FILE * tm=fopen(date,"r");
	char TM[20];
	fscanf(tm,"%s",TM);
	printf("%s\n",TM);
	fclose(dt);
	fclose(tm);
}