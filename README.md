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

I use the function arg_ok that verifies those four arguments, prints all error messages related to such verification.
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
### Allowed functions

There are 18 allowed functions for Pipex. All of them belong to the set of 51 functions allowed in minishell. I summarize them here. It is work in advance to understand minishell.


|Library|Function|Description|
|-------|-----|-------------------------------------------------------------------------------------|
|fcntl.h|open|The open() system call opens/creates the file specified by pathname in read/write mode if currente permission allow it. I used it with file1 and file2. <br> O_CLOEXEC Enable  the  close‐on‐exec  flag for the new file descriptor. It is essential in some multithreaded programs to avoid race conditions where one thread opens a file descriptor and attempts to set its close‐on‐exec flag using fcntl(2) at the same  time  as  another  thread  does  a fork(2)  plus execve(2).  Depending on the order of execution, the race may lead to the file descriptor returned by open() being unintentionally leaked to the program executed by the child process created by fork(2). |
|stdio.h|perror|The perror() function produces a message on standard error describing the last error encountered during a call to a system or library function. The argument string s is printed, followed by a colon and a blank. Then an error message corresponding to the current value of errno and a new‐line. Joining "__func__" and "__LINE__" to string s i managed a more verbose error message.|
|stdlib.h|exit|The exit() function causes normal process termination and the least significant byte of status (i.e., status & 0xFF) is returned to the parent. The C standard specifies two constants, EXIT_SUCCESS and EXIT_FAILURE, that may be passed to exit() to indicate successful or unsuccessful termination, respectively. All open streams are flushed and closed. Temporal files created are removed.|
|stdlib.h|free|The free() function frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc().|
|stdlib.h|malloc|The malloc() function allocates size bytes and returns a pointer to the allocated memory. The memory is not initialized.|
|string.h|strerror|The strerror() function returns a pointer to a string that describes the error code passed in the argument errnum or "Unknown error nnn" if the error number is unknown. This string must not be modified by the application.|
|sys/wait.h|wait|All of these system calls are used to wait for state changes in a child of the calling process, and obtain information about the child whose state has changed. A state change is considered to be:<br><ul>the child terminated;</ul><br><ul> the child was stopped by a signal;</ul><br><ul> or the child was resumed by a signal.</ul><br><br>In the case of a terminated child, performing a wait allows the system to release the resources associated with the child; if a wait is not performed, then the terminated child remains in a "zombie" state (see NOTES below). The wait() system call suspends execution of the calling thread until one of its children terminates.|
|sys/wait.h|waitpid|The waitpid() system call suspends execution of the calling thread until a child specified by pid argument has changed state. By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument, as described below.|
|unistd.h|access|access() checks whether the calling process can access the file pathname. With mode F_OK cheks if file exists. On success, zero is returned. On error -1 is returned and errno indicates the error.|
|unistd.h|close| close()  closes  a file descriptor, so that it no longer refers to any file and may be reused.  Any record locks (see fcntl(2)) held on the file it was associated with, and owned by the process, are removed (regardless of the file descriptor that was used to obtain the lock).  If fd is the last file descriptor referring to the underlying open file description (see open(2)), the resources associated with the open file description are freed; if the  file descriptor was the last reference to a file which has been removed using unlink(2), the file is deleted. Returns zero on succsess. On error returns -1 and errno indicates the error.  |
|unistd.h|dup|The  dup()  system call allocates a new file descriptor(unused lowest-numbered) that refers to the same open file description as the descriptor oldfd.After a successful return, the old and new file descriptors may be used interchangeably.  Since the two file descriptors refer to the same open file description, they share  file offset and file status flags |
|unistd.h|dup2| The  dup2()  system  call performs the same task as dup(), but instead of using the lowest‐numbered unused file descriptor, it uses the file descriptor number specified in newfd.  In other words, the file descriptor newfd is adjusted so that it now refers to the same open file description as oldfd.  If the file descriptor newfd was previously open, it is closed silently (no error reported) before being reused. on success returns the new file descriptor. On error returns -1 and errno indicates the error.|
|unistd.h|execve|execve()  executes  the program referred to by pathname, that can be a binary executable or a script starting with a shebang line. This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.<br>execve()  does  not return on success, and the text, initialized data, uninitialized data (bss), and stack of the calling process are overwritten according to the contents of the newly loaded program. on error, -1 is returned and errno indicates the error. |
|unistd.h|fork| fork() creates a new process by duplicating the calling process.  The new process is referred to as the child process.  The calling process is referred to as the parent process.The child inherits copies of the parent’s set of open file descriptors.  Each file descriptor in the child refers to the same open file description (see open(2)) as the corre‐ sponding file descriptor in the parent.  On  success,  the  PID of the child process is returned in the parent, and 0 is returned in the child.  On failure, -1 is returned in the parent, no child process is created, and errno is set to indicate the error. |
|unistd.h|pipe| pipe()  creates  a  pipe, a unidirectional data channel that can be used for interprocess communication.  The array pipefd is used to return two file descriptors referring to the ends of the pipe.  pipefd[0] refers to the read end of the pipe.  pipefd[1] refers to the write end of the pipe.  Data written to the write end of the pipe  is  buffered  by  the kernel until it is read from the read end of the pipe.|
|unistd.h|read| read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.If count is zero, read() may detect error EISDIR to check that fd is a directory. on success, the number of bytes read is returned.|
|unistd.h|unlink|unlink() deletes a name from the filesystem.  If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.  |
|unistd.h|write|write() writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd. If  count is zero and fd refers to a regular file, then write() may return a failure status EPIPE for a file descriptor conected to a pipe whose reading end is closed |


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

The variable environ points to an array of pointers to strings called the "environment". The last pointer in this array has the value NULL.

This array of strings is made available to the process by the execve(2) call when a new program is started.

When a child process is created via fork(2), it inherits a copy of its parent’s environment.


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

Said that, "grep -n printf" transforms easily into a list of strings args ={"grep", "-n", "printf", NULL} wiht the help of ft_plit and white space. 

In the same way, "tr 'a' 'e'", also fits into execve without problems.

It is not the case with, "tr 'a' ''", that substitutes a by ' if passed as {"tr", "'a'", "'", NULL}
It is not the case wiht, "tr 'a' ' '", that does not execute if passed as {"tr", "'a'", "'", "'", NULL}

## What I read.

[Here doc](https://linuxize.com/post/bash-heredoc/)
