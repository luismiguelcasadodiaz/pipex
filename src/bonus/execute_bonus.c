/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/25 13:03:49 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "ft_error.h"
#include "libft.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

static void	my_close(int fd)
{
	int	r;
	r = close(fd);
	if (r)
		perror("Error closing file");
}

static void	close_pipes(t_pipex_args args)
{
	int i;

	i = 0;
	while (i < args.num_cmds)
	{
		my_close(args.cmds[i]->pfd[0]);
		my_close(args.cmds[i]->pfd[1]);
		i++;
	}
}

static void	close_pipes_but_mine(t_pipex_args args)
{
	int i;

	fprintf(stderr,"i am cmd[%d] closing fds=[",args.exe_cmds);
	i = 0;
	while (i < args.exe_cmds)
	{
		my_close(args.cmds[i]->pfd[0]);
		my_close(args.cmds[i]->pfd[1]);
		printf("%d,%d,", args.cmds[i]->pfd[0], args.cmds[i]->pfd[1]);
		i++;
	}
	
	//dup2(args.cmds[i]->pfd[READ], 0);
	//my_close(args.cmds[i]->pfd[READ]);
	my_close(args.cmds[i]->pfd[WRITE]);
	fprintf(stderr,"%d,", args.cmds[i]->pfd[WRITE]);
	i++;
	
	my_close(args.cmds[i]->pfd[READ]);
	//dup2(args.cmds[i]->pfd[WRITE], 1);
	//my_close(args.cmds[i]->pfd[WRITE]);
	fprintf(stderr,"%d,", args.cmds[i]->pfd[READ]);
	i++;
	
	while (i < args.num_cmds)
	{
		fprintf(stderr,"%d,%d,", args.cmds[i]->pfd[0], args.cmds[i]->pfd[1]);
		my_close(args.cmds[i]->pfd[0]);
		my_close(args.cmds[i]->pfd[1]);
		i++;
	}
	fprintf(stderr,"]\n");
}
/*
static void	cmd_0(t_pipex_args args, char **env)
{

	read_or_exit(args, 0);
	if (dup2(args.cmds[0]->fd_i, 0) == -1)
		perror("Error dup infile");
	else
	{
		close(args.cmds[0]->pfd[READ]);
		if (dup2(args.cmds[1]->pfd[READ], 1) == -1)
			perror("Error dup outfile ");
		else
		{
			close(args.cmds[0]->fd_i);
			close(args.cmds[0]->pfd[WRITE]);
			//close_pipes(args);
			show_pipex_args(args);
			execve(args.cmds[0]->cmd, args.cmds[0]->flg, env);
			if (!args.cmds[0]->is_r)
				my_perror(args.cmds[0]->cli, ": command not found");
			else if (!args.cmds[0]->is_x)
				my_perror(args.cmds[0]->cli, ": permission denied");
		}
	}
}
*/

/*
static void	cmd_1(t_pipex_args args, char **env)
{ int	idx;
	idx = args.max_cmds -1;
	write_or_exit(args, idx);
	if (dup2(args.cmds[idx]->fd_o, 1) == -1)
		perror("Error dup infile");
	else
	{
		close(args.cmds[idx]->fd_o);
		close(args.cmds[idx]->pfd[WRITE]);
		if (dup2(args.cmds[0]->pfd[WRITE], 0) == -1)
			perror("Error dup outfile ");
		else
		{
			close(args.cmds[idx]->pfd[READ]);
			//close_pipes(args);
			show_pipex_args(args);
			execve(args.cmds[idx]->cmd, args.cmds[idx]->flg, env);
		}
	}
}
*/
static void	cmd_n(t_pipex_args args, char **env)
{
	fprintf(stderr,"alive %d\n", args.exe_cmds);
	open_or_exit(args);
	close_pipes_but_mine(args);
	show_pipex_args(args);
	execve(args.cmds[args.exe_cmds]->cmd, args.cmds[args.exe_cmds]->flg, env);
	if (args.exe_cmds == 0)
	{
		if (!args.cmds[0]->is_r)
			my_perror(args.cmds[0]->cli, ": command not found");
		else if (!args.cmds[0]->is_x)
			my_perror(args.cmds[0]->cli, ": permission denied");
	}
	close(0);
	close(1);
	close(2);
}
/*
static int	set_exit_error(t_pipex_args args)
{
	int	error;

	close_pipes(args);
	error = -1;
	if (!args.cmds[args.max_cmds -1]->is_r)
	{
		error = 127;
		my_perror(args.cmds[args.max_cmds -1]->cli, ": command not found");
	}
	else if (!args.cmds[args.max_cmds -1]->is_x)
	{
		error = 126;
		my_perror(args.cmds[args.max_cmds -1]->cli, ": permission denied");
	}
	return (error);
}
*/
void	execute(t_pipex_args args, char **env)
{
	int	error;

	while (args.exe_cmds < args.max_cmds)
	{
		fprintf(stderr,"creating %d of %d\n", args.exe_cmds, args.max_cmds);
		args.cmds[args.exe_cmds]->pid = fork();
		if (args.cmds[args.exe_cmds]->pid < 0)
		{
			close_pipes(args);
			ft_error_exit(errno, __func__, __LINE__);
		}
		if (args.cmds[args.exe_cmds]->pid == 0)
		{ 
			cmd_n(args, env);
		}
		else
		{
			waitpid(args.cmds[args.exe_cmds]->pid, &error, 0);
		}
		args.exe_cmds++;
		
	}
	close_pipes(args);
}
