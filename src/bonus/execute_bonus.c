/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/04/08 09:37:21 by luicasad         ###   ########.fr       */
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

static void	my_close(int who, int fd, const char *func, int line)
{
	int		r;
	char	*loc;
	char	*txt;
	char	*aux;
	char	*aux2;

	aux = ft_itoa(fd);
	txt = ft_strjoin("Error closing file ", aux);
	free(aux);
	aux = ft_itoa(who);
	loc = ft_strjoin(" Process[", aux);
	free(aux);
	aux = ft_strjoin(loc, "] ");
	free(loc);
	loc = ft_itoa(line);
	aux2 = ft_strjoin(aux, loc);
	free(aux);
	free(loc);
	aux = ft_strjoin(aux2, " ");
	free(aux2);
	loc = ft_strjoin(func, aux);
	free(aux);
	r = close(fd);
	if (r)
		my_perror(loc, txt);
	else
		fprintf(stderr, "closed [%d]  ", fd);
	free(txt);
	free(loc);
}

static void	close_pipes(t_pipex_args args)
{
	int	i;

	i = 0;
	while (i < args.num_cmds)
	{
		my_close(args.exe_cmds, args.cmds[i]->pfd[0], __func__, __LINE__);
		my_close(args.exe_cmds, args.cmds[i]->pfd[1], __func__, __LINE__);
		i++;
	}
}
/*  
static void	close_mine_pipes(t_pipex_args args)
{
	if (args.exe_cmds != args.num_cmds)
		my_close(args.exe_cmds, args.cmds[args.exe_cmds]->pfd[WRITE], __func__, __LINE__);
	if (args.exe_cmds != 0)
		my_close(args.exe_cmds, args.cmds[args.exe_cmds - 1]->pfd[READ], __func__, __LINE__);
}
  */
static void	close_pipes_but_mine(t_pipex_args args)
{
	int	i;

	fprintf(stderr, "i am cmd[%d] closing fds=[", args.exe_cmds);
	if (args.exe_cmds == 0)
	{
		my_close(args.exe_cmds, args.cmds[0]->pfd[READ], __func__, __LINE__);
		i = 1;
		while (i < args.num_cmds)
		{
			my_close(args.exe_cmds, args.cmds[i]->pfd[READ], __func__, __LINE__);
			my_close(args.exe_cmds, args.cmds[i++]->pfd[WRITE], __func__, __LINE__);
		}
	}
	else if ((1 <= args.exe_cmds) && (args.exe_cmds < args.num_cmds - 1))
	{
		i = 0;
		while (i < args.exe_cmds -1)
		{
			my_close(args.exe_cmds, args.cmds[i]->pfd[READ], __func__, __LINE__);
			my_close(args.exe_cmds, args.cmds[i++]->pfd[WRITE], __func__, __LINE__);
		}
		my_close(args.exe_cmds, args.cmds[args.exe_cmds - 1]->pfd[WRITE], __func__, __LINE__);
		my_close(args.exe_cmds, args.cmds[args.exe_cmds]->pfd[READ], __func__, __LINE__);
		i = args.exe_cmds + 1;
		while (i < args.num_cmds)
		{
			my_close(args.exe_cmds, args.cmds[i]->pfd[READ], __func__, __LINE__);
			my_close(args.exe_cmds, args.cmds[i++]->pfd[WRITE], __func__, __LINE__);
		}
	}
	else
	{
		i = 0;
		while (i < args.num_cmds - 2)
		{
			my_close(args.exe_cmds, args.cmds[i]->pfd[READ], __func__, __LINE__);
			my_close(args.exe_cmds, args.cmds[i++]->pfd[WRITE], __func__, __LINE__);
		}
		my_close(args.exe_cmds, args.cmds[i]->pfd[WRITE], __func__, __LINE__);
		i++;
		my_close(args.exe_cmds, args.cmds[i]->pfd[READ], __func__, __LINE__);
		my_close(args.exe_cmds, args.cmds[i]->pfd[WRITE], __func__, __LINE__);
	}
	fprintf(stderr, "%s\n", "]");
}

static int	set_exit_error(t_pipex_args args)
{
	int	error;

	//close_pipes(args);
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

static void	cmd_n(t_pipex_args args, char **env)
{
	fprintf(stderr, "\nalive %d  ", args.exe_cmds);
	close_pipes_but_mine(args);
	open_or_exit(args);
	show_pipex_args(args);
	execve(args.cmds[args.exe_cmds]->cmd, args.cmds[args.exe_cmds]->flg, env);
	//close_mine_pipes(args);
	if (args.exe_cmds < args.num_cmds)
	{
		if (!args.cmds[0]->is_r)
			my_perror(args.cmds[0]->cli, ": command not found");
		else if (!args.cmds[0]->is_x)
			my_perror(args.cmds[0]->cli, ": permission denied");
	}
	else
		exit(set_exit_error(args));
}

void	execute(t_pipex_args args, char **env)
{
	int		error;
	int		i;
	short	child;

	child = 0;

	while (args.exe_cmds < args.max_cmds)
	{
		fprintf(stderr, "creating %d of %d\n", args.exe_cmds, args.max_cmds);
		args.cmds[args.exe_cmds]->pid = fork();
		if (args.cmds[args.exe_cmds]->pid < 0)
		{
			close_pipes(args);
			ft_error_exit(errno, __func__, __LINE__);
		}
		if (args.cmds[args.exe_cmds]->pid == 0)
		{
			cmd_n(args, env);
			child = 1;
			args.exe_cmds = args.max_cmds - 1;
		}
		args.exe_cmds++;
	}
	if (!child)
	{
		close_pipes(args);
		i = 0;
		while (i < args.max_cmds)
		{
			waitpid(args.cmds[i]->pid, &error, 0);
			if (WIFEXITED(error))
				fprintf(stderr, "[%d] %s ==> exited with %d\n", i, args.cmds[i]->cli, WEXITSTATUS(error));
			i++;
		}
	}
}
