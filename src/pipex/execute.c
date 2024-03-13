/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/11 17:05:08 by luicasad         ###   ########.fr       */
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

static void	my_perror(char *a, char *b)
{
	char	*j;
	char	*i;

	if (b)
	{
		j = ft_strjoin(a, b);
		i = ft_strjoin("pipex: ", j);
		ft_printf("%s\n", i);
		free(j);
		free(i);
	}
	else
	{
		j = ft_strjoin("pipex: ", a);
		perror(j);
		free(j);
	}
}

static void	cmd_0(t_pipex_args args, char **env, int apipe[])
{
	args.cmds[0]->fd_i = open(args.infile, O_RDONLY);
	if (args.cmds[0]->fd_i == -1)
	{
		my_perror(args.in_arg, NULL);
		exit(1);
	}
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
					my_perror(args.cmds[0]->cli, ": command not found");
				else if (!args.cmds[0]->is_x)
					my_perror(args.cmds[0]->cli, ": permission denied");
			}
		}
	}
}

static void	cmd_1(t_pipex_args args, char **env, int apipe[])
{
	int	idx;
	int	error;

	error = 0;
	idx = args.max_cmds -1;
	args.cmds[idx]->fd_o = open(args.outfile, \
				O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (args.cmds[idx]->fd_o == -1)
	{
		my_perror("P1pex: ", args.ou_arg);
		exit(1);
	}
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
				execve(args.cmds[idx]->cmd, args.cmds[idx]->flg, env);
		}
	}
}

static int	set_exit_error(t_pipex_args args)
{
	int	error;

	error = -1;
	if (!args.cmds[args.max_cmds -1]->ok)
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
		cmd_1(args, env, pfd);
		exit(set_exit_error(args));
	}
	close(pfd[0]);
	close(pfd[1]);
}
