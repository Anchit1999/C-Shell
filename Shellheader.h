#ifndef Anchit_Shell
#define Anchit_Shell

typedef struct Jobs
{
	char time[20];
	char c[10];
	char name[50];
	char id[20];
}jobs;
jobs JB[500];
typedef long long int ll;
char *root;
int qt,pp,fgpid,Run,myMAINpid,myCHILDpid;
char *bgexit[40000];
char* rel_path(char * cwd);

void handle_sigint(int sig);

void shell_prompt();

char * commands();

char **split_SCcommand(char *cmd);

char **split_command(char * cmd,char * DLM);

char **split_echoqcommand(char * cmd);

void my_echo(char **args);

void my_pwd(char **args);

void my_pinfo(char **args);

void my_ls(char **args);

void execute_cmd(char **args);

void my_remindme(char **args);

void my_cd(char **args,int bg);

void my_clock();

void my_redirect(char **args);

void my_pipe(char *cmd);

void my_setenv (char **args);

void my_unsetenv (char **args);

void my_jobs(int flag);

void my_kjob(char **args);

void my_fg(char **args);

void my_bg(char **args);

void my_overkill();

#endif