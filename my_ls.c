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

int flag=0;
void my_ls(char **args)
{
	char *color;
	color = malloc(100);
	int ccc=0;
	while(args[ccc]!=NULL)
	{
		// printf("%s\n",args[ccc]);
		ccc++;
	}
	int dash=1,ls_dir=0,isDIr=0;
	struct dirent **ls_name;
	int no,ls_a=0,ls_l=0,ls_al=0;
	int COUNT[1000]={0};
	if(args[1]==NULL)
	{
		// printf("args[1] is nulll\n");
		isDIr=1;
		no = scandir(".",&ls_name,NULL,alphasort);
		args[1] = malloc(100);
		strcpy(args[1],".");
		ccc++;
	}
	else
	{
		while(args[dash]!=NULL)
		{
			int c=1;
			if(args[dash][0]=='-')
			{
				while(args[dash][c]!='\0')
				{
					if(args[dash][c]=='a') ls_a=1;
					else if(args[dash][c]=='l') ls_l=1;
					else flag=1;
					COUNT[dash]=1;
					c++;
				}
			}
			dash++;
		}
		// if((ls_a || ls_l) && args[1]!=NULL)
		// {
		if(args[2]==NULL && COUNT[1]==1)
		{
			args[2] = malloc(100);
			strcpy(args[2],".");
			ccc++;
		}
		if(args[3]==NULL && COUNT[2]==1)
		{
			args[3] = malloc(100);
			strcpy(args[3],".");
			ccc++;
		}
		// }

	}
	// printf("%d\n",ccc);
	if(flag)
	{
		printf("Command not found\n");
	}
	else
	{
		char ls_rel[1000];
		char org[1000];
		struct stat dir;
		struct stat filename;
		struct stat syml;
		struct passwd *usr;
		struct group *gp;
		for(int i_ls=1;i_ls<ccc;i_ls++)
		{
			if(COUNT[i_ls]==0)
			{
				strcpy(org,args[i_ls]);
				if(args[i_ls][0]=='~')
				{
					strncpy(ls_rel,args[i_ls]+1,strlen(args[i_ls]));
					strcpy(args[i_ls],root);
					strcat(args[i_ls],ls_rel);
				}
				// printf("%s %d\n", args[i_ls],stat(args[i_ls],&dir));
				if(stat(args[i_ls],&dir)!=-1)
				{
					if(S_ISDIR(dir.st_mode))
					{
						isDIr=1;
						no = scandir(args[i_ls],&ls_name,NULL,alphasort);
						if(no<0 && isDIr==0) perror("ls");
						else
						{
						// printf("%d\n",no);
							printf("%s:\n\n",org);
							for(int i=0;i<no;i++)
							{
								strcpy(color,RESET);
								char *ab = malloc(100*sizeof(char));
								if(args[i_ls]==NULL)
									strcpy(ab,".");
								else
									strcpy(ab,args[i_ls]);
								strcat(ab,"/");
								strcat(ab,ls_name[i]->d_name);
					// printf("%s\n",ab);
								if((ls_name[i]->d_name)[0]!='.' || ls_a)
								{
						// printf("%s\t",ab );
									stat(ab,&filename);
									if(filename.st_mode & S_IXUSR || filename.st_mode & S_IXGRP || filename.st_mode & S_IXOTH)
										strcpy(color,GREEN);
									if(lstat(ab,&filename) != -1 && S_ISLNK(filename.st_mode))
									{
										strcpy(color,MAG);
										if(ls_l)
											printf("l");
									}
									else
									{
										if(S_ISDIR(filename.st_mode))
											strcpy(color,CYAN);
										if(ls_l)
											printf( (S_ISDIR(filename.st_mode)) ? "d" : "-");
									}
									if(ls_l)
									{
										printf( (filename.st_mode & S_IRUSR) ? "r" : "-");
										printf( (filename.st_mode & S_IWUSR) ? "w" : "-");
										printf( (filename.st_mode & S_IXUSR) ? "x" : "-");
										printf( (filename.st_mode & S_IRGRP) ? "r" : "-");
										printf( (filename.st_mode & S_IWGRP) ? "w" : "-");
										printf( (filename.st_mode & S_IXGRP) ? "x" : "-");
										printf( (filename.st_mode & S_IROTH) ? "r" : "-");
										printf( (filename.st_mode & S_IWOTH) ? "w" : "-");
										printf( (filename.st_mode & S_IXOTH) ? "x" : "-");

										printf(" %d ",(int)filename.st_nlink);
										usr = getpwuid(filename.st_uid);
										printf("%s ",usr->pw_name);
										gp = getgrgid(filename.st_uid);
										printf("%s ",gp->gr_name);
										printf("%lld ",(ll)filename.st_size);
										char *date_time = (char*)malloc(20*sizeof(char));
										strftime(date_time,20,"%b %d %H:%M",localtime(&(filename.st_ctime)));
										printf("%s ",date_time);
									}
									// printf("%s",color);
									printf("%s\t",ls_name[i]->d_name);
									if(ls_l) printf("\n");
									// printf("%s",RESET );
								}
								free(ls_name[i]);
								free(ab);
							}
							printf("\n");
							free(ls_name);
						// else
						// {
						// 	for(int i=0;i<no;i++)
						// 	{
						// 		if((ls_name[i]->d_name)[0]!='.' || ls_a)
						// 			printf("%s\t",ls_name[i]->d_name);
						// 		free(ls_name[i]);
						// 	}
						// 	printf("\n");
						// 	free(ls_name);
						// }
						}
					}
					else
					{
						stat(args[i_ls],&filename);
						if(filename.st_mode & S_IXUSR || filename.st_mode & S_IXGRP || filename.st_mode & S_IXOTH)
							strcpy(color,GREEN);
						if(lstat(args[i_ls],&filename) != -1 && S_ISLNK(filename.st_mode))
						{
							strcpy(color,MAG);
							if(ls_l)
								printf("l");
						}
						else
						{
							if(ls_l)
								printf("-");
						}
						if(ls_l)
						{
							printf( (filename.st_mode & S_IRUSR) ? "r" : "-");
							printf( (filename.st_mode & S_IWUSR) ? "w" : "-");
							printf( (filename.st_mode & S_IXUSR) ? "x" : "-");
							printf( (filename.st_mode & S_IRGRP) ? "r" : "-");
							printf( (filename.st_mode & S_IWGRP) ? "w" : "-");
							printf( (filename.st_mode & S_IXGRP) ? "x" : "-");
							printf( (filename.st_mode & S_IROTH) ? "r" : "-");
							printf( (filename.st_mode & S_IWOTH) ? "w" : "-");
							printf( (filename.st_mode & S_IXOTH) ? "x" : "-");

							printf(" %d ",(int)filename.st_nlink);
							usr = getpwuid(filename.st_uid);
							printf("%s ",usr->pw_name);
							gp = getgrgid(filename.st_uid);
							printf("%s ",gp->gr_name);
							printf("%lld ",(ll)filename.st_size);
							char *date_time = (char*)malloc(20*sizeof(char));
							strftime(date_time,20,"%b %d %H:%M",localtime(&(filename.st_ctime)));
							printf("%s ",date_time);
						}
						// printf("%s",color);
						printf("%s\n",args[i_ls]);
						// printf("%s",RESET);
					}
				}
				else
				{
					perror("ls");
				}
			}
		}
	}
	return;
}