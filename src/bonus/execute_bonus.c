/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/04/29 11:34:34 by luicasad         ###   ########.fr       */
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

	txt = ft_strjoin_int("Error closing file ", fd);
	loc = ft_strjoin_int(" Process[", who);
	aux = ft_strjoin(loc, "] ");
	free(loc);
	aux2 = ft_strjoin_int(aux, line);
	free(aux);
	aux = ft_strjoin(aux2, " ");
	free(aux2);
	loc = ft_strjoin(func, aux);
	free(aux);
	r = close(fd);
	if (r)
	{
		my_perror(loc, txt);
	}
	free(txt);
	free(loc);
}

static void	cmd_n_close_files(t_pipex_args a)
{
	my_close(a.exe_cmds, a.one_pipe[READ], __func__, __LINE__);
	if (a.exe_cmds < a.num_cmds - 1)
	{
		if (dup2(a.one_pipe[WRITE], STDOUT_FILENO) == -1)
			ft_error_exit(ERR007, __func__, __LINE__);
		else
		{
			my_close(a.exe_cmds, a.one_pipe[WRITE], __func__, __LINE__);
			my_close(a.exe_cmds, a.fd_o, __func__, __LINE__);
		}
	}
	else
	{
		if (dup2(a.fd_o, STDOUT_FILENO) == -1)
			ft_error_exit(ERR007, __func__, __LINE__);
		else
		{
			my_close(a.exe_cmds, a.one_pipe[WRITE], __func__, __LINE__);
			my_close(a.exe_cmds, a.fd_o, __func__, __LINE__);
		}
	}
}

static int	set_exit_error(t_pipex_args args, int error)
{
	if ((error == 2) || (error == 14))
	{
		error = 127;
		my_perror(args.cmds[args.max_cmds -1]->cli, "<: command not found");
	}
	else if (error == 13)
	{
		error = 126;
		my_perror(args.cmds[args.max_cmds -1]->cli, "<: permission denied");
	}
	return (error);
}

static void	cmd_n(t_pipex_args args, char **env)
{
	int	numerr;

	cmd_n_close_files(args);
	execve(args.cmds[args.exe_cmds]->cmd, \
				args.cmds[args.exe_cmds]->flg, env);
	numerr = errno;
	if (args.exe_cmds < args.num_cmds -1)
	{
		if ((numerr == 2) || (numerr == 14))
			my_perror(args.cmds[args.exe_cmds]->cli, ": command not found");
		if (numerr == 13)
			my_perror(args.cmds[args.exe_cmds]->cli, ": permission denied");
	}
	else
		exit(set_exit_error(args, numerr));
}

static void	execute_open_files(t_pipex_args *args)
{
	args->fd_i = open(args->infile, O_RDONLY);
	if (args->fd_i == -1)
	{
		my_perror(args->in_arg, NULL);
		exit(1);
	}
	if ((dup2(args->fd_i, STDIN_FILENO) == -1))
		ft_error_exit(ERR007, __func__, __LINE__);
	my_close(-1, args->fd_i, __func__, __LINE__);
	args->fd_o = open(args->outfile, \
	O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (args->fd_o == -1)
	{
		my_perror("P1pex: ", args->ou_arg);
		exit(1);
	}
}

static int	execute_father(t_pipex_args *args)
{
	int		error;

	my_close(-1, args->one_pipe[WRITE], __func__, __LINE__);
	if ((args->exe_cmds < args->max_cmds - 1) && \
			dup2(args->one_pipe[READ], STDIN_FILENO) == 1)
		ft_error_exit(ERR007, __func__, __LINE__);
	my_close(-1, args->one_pipe[READ], __func__, __LINE__);
	waitpid(args->cmds[args->exe_cmds]->pid, &error, 0);
	if (WIFEXITED(error))
	{
		if (WEXITSTATUS(error))
			return (WEXITSTATUS(error));
	}
	return (0);
}

int	execute(t_pipex_args args, char **env)
{
	int		iamchild;
	int		error_code;

	iamchild = 0;
	execute_open_files(&args);
	while (args.exe_cmds < args.max_cmds)
	{
		if (pipe(args.one_pipe) < 0)
			ft_error_exit(ERR021, __func__, __LINE__);
		args.cmds[args.exe_cmds]->pid = fork();
		if (args.cmds[args.exe_cmds]->pid < 0)
			ft_error_exit(errno, __func__, __LINE__);
		if (args.cmds[args.exe_cmds]->pid == 0)
		{
			cmd_n(args, env);
			args.exe_cmds = args.max_cmds - 1;
			iamchild = 1;
		}
		else
			error_code = execute_father(&args);
		args.exe_cmds++;
	}
	if (!iamchild)
		my_close(-1, args.fd_o, __func__, __LINE__);
	return (error_code);
}
