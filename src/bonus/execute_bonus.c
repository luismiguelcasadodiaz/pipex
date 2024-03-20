/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/20 12:26:40 by luicasad         ###   ########.fr       */
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

static void	close_pipes(t_pipex_args args)
{
	int i;

	i = 0;
	while (i < args.num_cmds)
	{
		close(args.cmds[i]->pfd[0]);
		close(args.cmds[i]->pfd[1]);
		i++;
	}
}

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

static void	cmd_1(t_pipex_args args, char **env)
{
	int	idx;


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

static void	cmd_n(t_pipex_args args, char **env)
{
	if (args.exe_cmds == 0)
	{
		read_or_exit(args, 0);
		if (dup2(args.cmds[0]->fd_i, 0) == -1)
			perror("Error dup infile");
	}
	if (args.exe_cmds == args.max_cmds - 1)
	{
		write_or_exit(args, 0);
		if (dup2(args.cmds[idx]->fd_o, 1) == -1)
			perror("Error dup infile");
	}
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
void	execute(t_pipex_args args, char **env)
{
	int	error;

	pid_t	pid1;
	while (args.exe_cmds < args.max_cmds)
	{
		pid1 = fork();
		if (pid1 < 0)
			ft_error_exit(errno, __func__, __LINE__);
		if (pid1 == 0)
			cmd_n(args, env);
		else
			waitpid(pid1, &error, 0);
		args.exe_cmds++;
	}
	close_pipes(args);















}
