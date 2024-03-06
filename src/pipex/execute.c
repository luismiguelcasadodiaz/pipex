/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/06 12:42:00 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include "ft_error.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

void	cmd_0(t_pipex_args args, char **env, int apipe[])
{
	int	error;

	args.cmds[0]->fd_i = open(args.infile, O_RDONLY);
	if (args.cmds[0]->fd_i == -1)
		ft_error_exit(ERR010, __func__, __LINE__);
	error = dup2(args.cmds[0]->fd_i, 0);
	if (error == -1)
		ft_error_exit(ERR007, __func__, __LINE__);
	close(apipe[READ]);
	error = dup2(apipe[WRITE], 1);
	if (error == -1)
		ft_error_exit(ERR007, __func__, __LINE__);
	if (args.cmds[0]->ok)
		execve(args.cmds[0]->cmd, args.cmds[0]->flg, env);
	close(args.cmds[0]->fd_i );
	close(args.cmds[0]->fd_o );
	ft_error_exit(ERR127, __func__, __LINE__);
}

void	cmd_1(t_pipex_args args, char **env, int apipe[])
{
	int	idx;
	int	error;

	idx = args.max_cmds -1;
	args.cmds[idx]->fd_o = open(args.outfile, \
				O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (args.cmds[idx]->fd_o == -1)
		ft_error_exit(ERR010, __func__, __LINE__);
	error = dup2(args.cmds[idx]->fd_o, 1);
	if (error == -1)
		ft_error_exit(ERR007, __func__, __LINE__);
	close(apipe[WRITE]);
	error = dup2(apipe[READ], 0);
	if (error == -1)
		ft_error_exit(ERR007, __func__, __LINE__);
	if (args.cmds[idx]->ok)
		execve(args.cmds[idx]->cmd, args.cmds[idx]->flg, env);
	close(args.cmds[idx]->fd_i );
	close(args.cmds[idx]->fd_o );
	ft_error_exit(ERR127, __func__, __LINE__);
}
void	father(t_pipex_args args, char **env, int apipe[], int pid)
{
	int	idx;
	int	error;

	idx = args.max_cmds -1;
	close(apipe[WRITE]);
	error = dup2(apipe[READ], 0);
	if (error == -1)
		ft_error_exit(ERR007, __func__, __LINE__);
	waitpid(pid, &error, 0);
	if (!error)
	{
		args.cmds[idx]->fd_o = open(args.outfile, \
				O_TRUNC | O_WRONLY | O_CREAT, 0664);
		if (args.cmds[idx]->fd_o == -1)
			ft_error_exit(ERR010, __func__, __LINE__);
		dup2(args.cmds[idx]->fd_o, 1);
		if (error == -1)
			ft_error_exit(ERR007, __func__, __LINE__);
		execve(args.cmds[idx]->cmd, args.cmds[idx]->flg, env);
		ft_error_exit(ERR051, __func__, __LINE__);
	}
	else
		ft_printf("Son %s result %d\n", args.cmds[0]->cmd, error);
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
		ft_error_exit(ERR020, __func__, __LINE__);
	if (pid1 == 0)
		cmd_0(args, env, pfd);
	else
	{
		waitpid(pid1, &error, 0);
		cmd_1(args, env, pfd);
	}
}
