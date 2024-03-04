/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/04 13:37:03 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include "ft_error.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

void	son(t_pipex_args args, char **env, int apipe[])
{
	close(apipe[READ]);
	dup2(apipe[WRITE], 1);
	dup2(open(args.infile, O_RDONLY), 0);
	execve(args.cmds[0]->cmd, args.cmds[0]->flg, env);
	ft_error_print(ERR051, __func__, __LINE__);
	exit(EXIT_FAILURE);
}

void	father(t_pipex_args args, char **env, int apipe[], int pid)
{
	int	idx;
	int	error;

	idx = args.max_cmds -1;
	close(apipe[WRITE]);
	dup2(apipe[READ], 0);
	waitpid(pid, &error, 0);
	if (!error)
	{
		dup2(open(args.outfile, O_WRONLY), 1);
		execve(args.cmds[idx]->cmd, args.cmds[idx]->flg, env);
		ft_error_print(ERR051, __func__, __LINE__);
		exit(EXIT_FAILURE);
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
		ft_error_print(ERR020, __func__, __LINE__);
	else if (pid == 0)
		son(args, env, pfd);
	else
		father(args, env, pfd, pid);
}
