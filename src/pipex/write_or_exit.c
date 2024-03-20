/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_or_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:22:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 11:56:08 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_error.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	write_or_exit(t_pipex_args args, int idx)
{
	args.cmds[idx]->fd_o = open(args.outfile, \
				O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (args.cmds[idx]->fd_o == -1)
	{
		my_perror("P1pex: ", args.ou_arg);
		exit(1);
	}
}
