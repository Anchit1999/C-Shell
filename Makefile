Shell: \
			main.o \
			rel_path.o \
			shell_prompt.o \
			commands.o \
			execute_cmd.o \
			my_echo.o \
			my_ls.o \
			my_pinfo.o \
			my_pwd.o \
			my_cd.o \
			my_redirect.o\
			my_env.o\
			my_pipe.o\
			my_jobs.o\
			my_kjob.o\
			my_fg.o\
			my_bg.o\
			my_overkill.o\
			my_clock.o \
			my_remindme.o \
			split_command.o
	gcc -g -o my_shell $^

clean:
	@rm -rf *.o Shell

main.o: Shellheader.h main.c
	gcc -g -c main.c

rel_path.o: Shellheader.h rel_path.c
	gcc -g -c rel_path.c

shell_prompt.o: Shellheader.h shell_prompt.c
	gcc -g -c shell_prompt.c

commands.o: Shellheader.h commands.c
	gcc -g -c commands.c

execute_cmd.o: Shellheader.h execute_cmd.c 
	gcc -g -c execute_cmd.c

my_echo.o: Shellheader.h my_echo.c
	gcc -g -c my_echo.c

my_ls.o: Shellheader.h my_ls.c
	gcc -g -c my_ls.c

my_pinfo.o: Shellheader.h my_pinfo.c
	gcc -g -c my_pinfo.c

my_cd.o: Shellheader.h my_cd.c
	gcc -g -c my_cd.c

my_pwd.o: Shellheader.h my_pwd.c
	gcc -g -c my_pwd.c
	
my_remindme.o: Shellheader.h my_remindme.c
	gcc -g -c my_remindme.c
	
split_command.o: Shellheader.h split_command.c 
	gcc -g -c split_command.c

my_clock.o: Shellheader.h my_clock.c
	gcc -g -c my_clock.c

my_redirect.o: Shellheader.h my_redirect.c
	gcc -g -c my_redirect.c
	
my_pipe.o: Shellheader.h my_pipe.c
	gcc -g -c my_pipe.c

my_env.o: Shellheader.h my_env.c
	gcc -g -c my_env.c

my_jobs.o: Shellheader.h my_jobs.c
	gcc -g -c my_jobs.c

my_kjob.o: Shellheader.h my_kjob.c
	gcc -g -c my_kjob.c

my_fg.o: Shellheader.h my_fg.c
	gcc -g -c my_fg.c

my_bg.o: Shellheader.h my_bg.c
	gcc -g -c my_bg.c

my_overkill.o: Shellheader.h my_overkill.c
	gcc -g -c my_overkill.c