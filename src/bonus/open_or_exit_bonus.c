/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_or_exit_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:18:36 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/28 14:08:09 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "ft_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	my_dup(int fd, int stdfile)
{
	if (dup2(fd, stdfile) == -1)
		perror("Error dup infile");
	close(fd);
	fprintf(stderr, "fd=[%d] duplicated as [%d]\n", fd, stdfile);
}

void	open_or_exit(t_pipex_args args)
{
	if (args.exe_cmds == 0)
	{
		args.cmds[args.exe_cmds]->fd_i = open(args.infile, O_RDONLY);
		if (args.cmds[args.exe_cmds]->fd_i == -1)
		{
			my_perror(args.in_arg, NULL);
			exit(1);
		}
		my_dup(args.cmds[args.exe_cmds]->fd_i, 0);
		my_dup(args.cmds[args.exe_cmds]->pfd[WRITE], 1);
	}
	else if ((1 <= args.exe_cmds) && (args.exe_cmds < (args.num_cmds - 1)))
	{
		my_dup(args.cmds[args.exe_cmds - 1]->pfd[READ], 0);
		my_dup(args.cmds[args.exe_cmds]->pfd[WRITE], 1);
	}
	else if (args.exe_cmds == args.num_cmds - 1)
	{
		args.cmds[args.exe_cmds]->fd_o = open(args.outfile, \
				O_TRUNC | O_WRONLY | O_CREAT, 0664);
		if (args.cmds[args.exe_cmds]->fd_o == -1)
		{
			my_perror("P1pex: ", args.ou_arg);
			exit(1);
		}
		my_dup(args.cmds[args.exe_cmds - 1]->pfd[READ], 0);
		my_dup(args.cmds[args.exe_cmds]->fd_o, 1);
	}
}
