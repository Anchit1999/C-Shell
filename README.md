Shell in C:
===========

Execution
---
Run the following commands on terminal:
```
    make
    ./my_shell
```

Features
---
  - Modular Code.
  - Self implemented cd,ls,pwd,echo.
  - ls with only [al] flags.
  - Colored output in ls.
  - Semicolon separated commands.
  - Foreground Background Implemented.
  - Piping and redirection
  - Signal handling(SIGINT,SIGTSTP).
  - Pinfo implemented for process information.
  - Bonus: Remindme and clock implemented.
  - exit for quitting the shell.

Other Builtin Commands
---
### Jobs:
* Displays all the running process of the shell
### Kjob:
* Usage: kjob [jobnumber] [signalNumber]
* Takes the job id of a running job and sends a signal value to that process
### setenv:
* Usage: setenv var [value]
* Set the value of var to value
### unsetenv:
* Usage: unsetenv var
* Destroy the environment variable var
### fg:
* Usage: fg [jobnumber]
*  brings a running or a stopped background job with given job number to foreground
### bg:
* Usage: bg [jobnumber]
*  changes a stopped background job to a running background
job
### overkill:
* kill all the background processes at once
 


Bonus Usage
---
#### Remindme:
Usage: remindme [time] [message]

#### Clock:
Usage: clock -t -[number of times to diplay date/time] [number: update based on fixed interval of time]
```
:~> clock -t -3 1
    2018-09-04 11:41:10
    2018-09-04 11:41:11
    2018-09-04 11:41:12 
```
   