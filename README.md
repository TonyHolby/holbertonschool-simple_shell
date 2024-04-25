# <p align="center">Project C - Simple Shell</p>

------
Description
------

This project is an implementation of a simple shell.
The shell function displays a prompt waiting for the user to type a command before executing it.
An infinite loop is running until a failure signal stop the loop.
The prompt is re-displayed each time a command has been executed.
The "end of file" condition is handled by Ctrl+D, which terminates the process.
It can be used in interactive or non-interactive mode.

-------
Requierments
-------

To compil this program it is necessary to use GCC (GNU Compiler Collection) 20.04 LTS.

-------
Compilation
------

The command to compil the program :

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

------
Examples
------

Here is some examples of the use of the simple shell in interactive mode :

```

standard shell# ./hsh
$ ls
README.md man_1_simple_shell AUTHORS shell.c
$ pwd
holbertonschool-simple_shell
$ 
$ exit
standard shell#

```

Here is some examples of the use of the simple shell in non-interactive mode :

```

standard shell# echo "/bin/ls" | ./hsh
README.md man_1_simple_shell AUTHORS shell.c arguments.c execute.c shell.h
standard shell# echo "/bin/pwd" | ./hsh
holbertonschool-simple_shell
standard shell#

```
------
Flowchart
------

![flowchart simple shell - C drawio](https://github.com/TonyHolby/holbertonschool-simple_shell/assets/159525275/f093b5ce-b2ef-478f-8661-d8c41b270a37)

------
Authors

Rosario GLE
Tony NEMOUTHE
