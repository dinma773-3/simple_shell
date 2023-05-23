# 0x16. C - Simple Shell
# Group Project

# Scope:
-Basics of programming
-Basics of C
-Basics of thinking like an engineer
-Group work
-Learning how to learn

# Objective:
-To know;
-Who designed and implemented the original Unix operating system
-Who wrote the first version of the UNIX shell
-Who invented the B programming language (the direct predecessor to the C programming language)
-Who is Ken Thompson
-How does a shell work
-What is a pid and a ppid
-How to manipulate the environment of the current process
-What is the difference between a function and a system call
-How to create processes
-What are the three prototypes of main
-How does the shell use the PATH to find the programs
-How to execute another program with the execve system call
-How to suspend the execution of a process until one of its children terminates
-What is EOF / “end-of-file”?

# History:
<<<<<<< HEAD
    1  cd simple_shell
    2  ls
    3  emacs 1-builtin.c
    4  fuser -k 1-builtin.c
    5  ls
    6  lsof -t 1-builtin.c
    7  ls
    8  emacs 1-builtin.c
    9  emacs exit.c
   10  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 exit.c -o hsh
   11  emacs exit.c
   12  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 exit.c -o hsh
   13  emacs exec.c
   14  emacs env.c
   15  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 env.c -o hsh
   16  emacs env.c
   17  emacs sell.h
   18  ls
   19  emacs shell.h
   20  emacs env.c
   21  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 env.c -o hsh
   22  emacs getline.c
   23  emacs getenv.c
   24  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 getenv.c -o hsh
   25  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 getline.c -o hsh
   26  emacs getline.c
   27  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 getline.c -o hsh
   28  emacs getline.c
   29  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 getline.c -o hsh
   30  emacs getline.c
   31  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 getline.c -o hsh
   32  emacs getline.c
   33  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 getline.c -o hsh
   34  emacs getline.c
   35  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 getline.c -o hsh
   36  history
=======
-Added in the _putchar function to the project  
-Created the project header file called "shell.h"  
-Added in the function prototype for _putchar to the header file.  
>>>>>>> 8cc08f4dabec802dc74f00b038e7f2a35452d8e4
