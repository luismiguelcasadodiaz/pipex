/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/04 22:33:42 by luicasad         ###   ########.fr       */
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

	close(apipe[READ]);
	error = dup2(apipe[WRITE], 1);
	if (error == -1)
		ft_error_exit(ERR007, __func__, __LINE__);
	args.cmds[0]->fd_i = open(args.infile, O_RDONLY);
	if (args.cmds[0]->fd_i == -1)
		ft_error_exit(ERR008, __func__, __LINE__);
	error = dup2(args.cmds[0]->fd_i, 0);
	if (error == -1)
		ft_error_exit(ERR007, __func__, __LINE__);
	execve(args.cmds[0]->cmd, args.cmds[0]->flg, env);
	ft_error_exit(ERR051, __func__, __LINE__);
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
		args.cmds[idx]->fd_o = open(args.outfile, O_TRUNC | O_WRONLY | O_CREAT, 0664);
		if (args.cmds[idx]->fd_o == -1)
			ft_error_exit(ERR008, __func__, __LINE__);
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
	pid_t	pid;

	pipe(pfd);
	pid = fork();
	if (pid < 0)
		ft_error_exit(ERR020, __func__, __LINE__);
	else if (pid == 0)
		cmd_0(args, env, pfd);
	else
		father(args, env, pfd, pid);
}
