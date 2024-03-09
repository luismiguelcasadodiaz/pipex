/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/09 16:39:39 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include "ft_error.h"
#include "libft.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

/*
void	cmd_0(t_pipex_args args, char **env, int apipe[])
{
	int	error;

	args.cmds[0]->fd_i = open(args.infile, O_RDONLY);
	if (args.cmds[0]->fd_i == -1)
		ft_error_print(errno, __func__, __LINE__);
	else
	{
		error = dup2(args.cmds[0]->fd_i, 0);
		if (error == -1)
			ft_error_exit(127, __func__, __LINE__);
		close(apipe[READ]);
		error = dup2(apipe[WRITE], 1);
		if (error == -1)
			ft_error_exit(errno, __func__, __LINE__);
		if (args.cmds[0]->ok)
			execve(args.cmds[0]->cmd, args.cmds[0]->flg, env);
		ft_error_exit(126, __func__, __LINE__);
	}
	exit(EXIT_FAILURE);
}

void	cmd_1(t_pipex_args args, char **env, int apipe[])
{
	int	idx;
	int	error;

	idx = args.max_cmds -1;
	args.cmds[idx]->fd_o = open(args.outfile, \
				O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (args.cmds[idx]->fd_o == -1)
		ft_error_print(errno, __func__, __LINE__);
	else
	{
		error = dup2(args.cmds[idx]->fd_o, 1);
		if (error == -1)
			ft_error_exit(errno, __func__, __LINE__);
		close(apipe[WRITE]);
		error = dup2(apipe[READ], 0);
		if (error == -1)
			ft_error_exit(errno, __func__, __LINE__);
		if (args.cmds[idx]->ok)
			execve(args.cmds[idx]->cmd, args.cmds[idx]->flg, env);
		ft_error_exit(ERR127, __func__, __LINE__);
	}
	exit(EXIT_FAILURE);
}


*/

 
void	cmd_0(t_pipex_args args, char **env, int apipe[])
{
	args.cmds[0]->fd_i = open(args.infile, O_RDONLY);
	if (args.cmds[0]->fd_i == -1)
		perror("Error infile");
	else
	{
		if (dup2(args.cmds[0]->fd_i, 0) == -1)
			perror("Error dup infile");
		else
		{
			close(apipe[READ]);
			if (dup2(apipe[WRITE], 1) == -1)
				perror("Error dup outfile ");
			else
			{
				execve(args.cmds[0]->cmd, args.cmds[0]->flg, env);
				if (!args.cmds[0]->ok)
					//exit(127);
					perror(ft_strjoin("command not found ", args.cmds[0]->cli));
				else
					exit(126);
			}
		}
	}
	exit(EXIT_FAILURE);
}

void	cmd_1(t_pipex_args args, char **env, int apipe[])
{
	int	idx;

	idx = args.max_cmds -1;
	args.cmds[idx]->fd_o = open(args.outfile, \
				O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (args.cmds[idx]->fd_o == -1)
		perror("Error infile");
	else
	{
		if (dup2(args.cmds[idx]->fd_o, idx) == -1)
			perror("Error dup infile");
		else
		{
			close(apipe[WRITE]);
			if (dup2(apipe[READ], 0) == -1)
				perror("Error dup outfile ");
			else
			{
				execve(args.cmds[idx]->cmd, args.cmds[idx]->flg, env);
				if (!args.cmds[idx]->ok)
					perror(ft_strjoin("command not found ", args.cmds[idx]->cli));
					//exit(127);
				else
					exit(126);
			}
		}
	}
	exit(EXIT_FAILURE);
}

/*
void	cmd_1(t_pipex_args args, char **env, int apipe[])
{
	int	idx;
	int	error;

	idx = args.max_cmds -1;
	args.cmds[idx]->fd_o = open(args.outfile, \
				O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (args.cmds[idx]->fd_o == -1)
		perror("outfile ");
	else
	{
		error = dup2(args.cmds[idx]->fd_o, 1);
		if (error == -1)
			ft_error_exit(errno, __func__, __LINE__);
		close(apipe[WRITE]);
		error = dup2(apipe[READ], 0);
		if (error == -1)
			ft_error_exit(errno, __func__, __LINE__);
		if (args.cmds[idx]->ok)
			execve(args.cmds[idx]->cmd, args.cmds[idx]->flg, env);
		ft_error_exit(ERR127, __func__, __LINE__);
	}
	exit(EXIT_FAILURE);
}
*/


void	execute(t_pipex_args args, char **env)
{
	int		pfd[2];
	pid_t	pid1;
	int		error;

	error = pipe(pfd);
	if (error < 0)
		ft_error_exit(ERR021, __func__, __LINE__);
	pid1 = fork();
	if (pid1 < 0)
		ft_error_exit(errno, __func__, __LINE__);
	if (pid1 == 0)
		cmd_0(args, env, pfd);
	else
	{
		waitpid(pid1, &error, 0);
		if (error == 126)
			perror(ft_strjoin("Permission denied", args.cmds[0]->cli));
		if (error == 127)
			perror(ft_strjoin("command not found", args.cmds[0]->cli));
		cmd_1(args, env, pfd);
		if (errno == 126)
			perror("Permission denied");
		exit(errno);
	}
	close(pfd[0]);
	close(pfd[1]);
}
