/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_or_exit_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:18:36 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 11:58:58 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	read_or_exit(t_pipex_args args, int idx)
{
	args.cmds[idx]->fd_i = open(args.infile, O_RDONLY);
	if (args.cmds[idx]->fd_i == -1)
	{
		my_perror(args.in_arg, NULL);
		exit(1);
	}
}
