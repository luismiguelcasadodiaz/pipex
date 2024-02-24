# pipex
This project will let you discover in detail a UNIX mechanism (pipes) that you already know by using it in your program.

Your program will be executed as follows:

```bash
./pipex file1 cmd1 cmd2 file2
```

It must take 4 arguments

file1 & file2 are file names
cmd1 and cmd2 are shell commands with their parameters.

I must behave exactly the same as this shell command

```bash
$> < file1 cmd1 | cmd2 > file2
```
# Approach

## Argument validation

For file1 check that there are reading permits
For file2 check that there are writing permits

check that either cmd1 or cmd2 are found in any path.

I use the funcition arg_ok that verifies that four argument, prints all error messages related to such verification.
If all four arguments are correct, arg_ok returns a struct with the right values to pass to the children processes

```c
typedef struct	s_pipex_args
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
}	t_pipex_args;
```
## What is a Shell command?

### According to `man bash`:
source, alias, bg, bind, break, builtin, caller, cd, command, compgen, complete, compopt, continue, declare, typeset, dirs, disown, echo, enable, eval, exec, exit, export, fc, fg, getopts, hash, help, history, jobs, kill, let, local, logout, mapfile, readarray, popd, printf, pushd, pwd, read, readonly, return, set, shift, shopt, suspend, test, times, trap, type, ulimit, umask, unalias, unset, wait, 

### According to `compgen -c`: 
MY linus box has 7717 commands

# Environment


I found two methods for getting the running enviroment of my a program

[Program Arguments](https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html)

[Environment Variables](https://www.gnu.org/software/libc/manual/html_node/Environment-Variables.html)

## Main Argument envp

In ISO C you can define main either to take no arguments, or to take two arguments that represent the command line arguments to the program, like this:

```c
int main (int argc, char *argv[])
```

In Unix systems you can define main a third way, using three arguments:

```c
int main (int argc, char *argv[], char *envp[])
```

The first two arguments are just the same. 
The third argument envp gives the program’s environment; it is the same as the value of environ. 

See Environment Variables. 

POSIX.1 does not allow this three-argument form, so to be portable **it is best to write main to take two arguments, and use the value of environ.**



```c
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int n;

	n = 0;
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
```

## Variable environ

The  variable  environ  points to an array of pointers to strings called the "environment".  The last pointer in this array has the value NULL.

This array of strings is made available to the process by the execve(2) call when a new program is started.

When a child  process  is  created via fork(2), it inherits a copy of its parent’s environment.


```c

#include <stdio.h>

int	main(int argc, char **argv)
{
	extern char **environ;
	int n;

	n = 0;
	while (*environ != NULL)
	{
		printf("%s\n", *environ);
		environ++;
	}
}
```

### Find a variable in enviromemt

Loops over environ matching var name, returning a apointer to the found var, NJULL oterhwise.

```c
char	*find_variable(char **environ, char	*var)
{
	int			len;

	len = ft_strlen(var);
	while (*environ != NULL)
	{
		result = ft_strnstr(*environ, var, len);
		if (result)
			return (*environ);
	}
	return (NULL);
}
```


