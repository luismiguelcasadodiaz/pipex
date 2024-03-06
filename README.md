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

## Bonus 1

Your program will be executed as follows:

```bash
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

## Bonus 2
Support « and » when the first parameter is "here_doc".


```bash
$> ./pipex here_doc LIMITER cmd cmd1 file
```

Should behave like:

```bash
cmd << LIMITER | cmd1 >> file
```

# Approach

## Argument validation

In mandatory part argc is 5. 5 minus pipex commnad minus infile minus outfile i have a two-commands pipe (5 - 3).
In bonus part argc is n. I have a (n - 3)-commnds pipe.

For file1 check that there are reading permits
For file2 check that there are writing permits

check that either cmd1 or cmd2 are found in any path.

I use the function arg_ok that verifies that four arguments, prints all error messages related to such verification.
If all four arguments are correct, arg_ok returns a struct with the right values to pass to the children processes.
The struct holds a all_ok variable that indicates if all filenames and commnads are reachable.
Also max_cmds and num_cmds help to manage the cmds malloc

```c
typedef struct	s_pipex_args
{
	int		max_cmds;
	int		num_cmds;
	char	*infile;
	char	*outfile;
	char	**cmds;
	int		all_ok;
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

### Find a variable in environmemt

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

### Find a command

Splits value of PATH variable. For each path, joins "/command" and checks if execution permit is possible.

Returns command full path or NULL if there are not execution permits.

```c
char	*arg_fin_com(char *var_val, char *com)
{
	char	**paths;
	char	*command;
	char	*result;
	char	*slash_command;
	int		len;

	slash_command = ft_strjoin("/", com);
	len = 0;
	result = NULL;
	paths = get_paths(var_val);
	while (paths[len] != NULL)
	{
		command = ft_strjoin(paths[len], slash_command);
		if (!result && !access(command, X_OK))
			result = command;
		len++;
	}
	return (result);
}
```

### find a file name

my first validation checks if filename has legal characters for a filename...any character except '/'.

Also, user may refer a filename with a relative path such as
../inc/filename
inc/filename

Then, if argument has not '/' it is a filename in current folder whose absolute path name start wiht the PWD variabla content

### The command and execve
The call to execve requires a null-terminated list of arguments

Said that, "grep -n printf" transforms easily into a list of strings args ={"grep", "-n", "printf", NULL} wiht the help of  ft_plit and white space. 

In the same way, "tr 'a' 'e'", also fits into execve without problems.

It is not the case with, "tr 'a' ''", that substitutes a by ' if passed as {"tr", "'a'", "'", NULL}
It is not the case wiht, "tr 'a' ' '", that does not execute if passed as {"tr",  "'a'", "'", "'", NULL}

## What I read.

[Here doc](https://linuxize.com/post/bash-heredoc/)
