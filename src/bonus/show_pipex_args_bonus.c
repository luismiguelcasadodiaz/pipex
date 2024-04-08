/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_pipex_args_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:47:06 by luicasad          #+#    #+#             */
/*   Updated: 2024/04/08 09:33:30 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "ft_printf.h"
#include <stdio.h>

void	show_pipex_args(t_pipex_args args)
{
	int	i;
	int	j;

	fprintf(stderr,"max_cmds %d\n", args.max_cmds);
	fprintf(stderr,"infile %s\n", args.infile);
	fprintf(stderr,"outfile %s\n", args.outfile);
	i = -1;
	while (++i < args.max_cmds)
	{
		fprintf(stderr,"cli %s \t\t--> cmds[%d] %s \tflgs: ", \
				args.cmds[i]->cli, i, args.cmds[i]->cmd);
		if (args.cmds[i]->flg)
		{
			j = 0;
			while (args.cmds[i]->flg[j] != NULL)
				fprintf(stderr,"%s ", args.cmds[i]->flg[j++]);
		}
		fprintf(stderr,"R_OK=%d ", args.cmds[i]->is_r);
		fprintf(stderr,"X_OK=%d ", args.cmds[i]->is_x);
		fprintf(stderr,"fd_i=%d ", args.cmds[i]->fd_i);
		fprintf(stderr,"fd_o=%d ", args.cmds[i]->fd_o);
		fprintf(stderr,"pipe[0]=%d ", args.cmds[i]->pfd[READ]);
		fprintf(stderr,"pipe[1]=%d ", args.cmds[i]->pfd[WRITE]);
		fprintf(stderr,"\n");
	}
	fprintf(stderr,"all_ok %d\n", args.all_ok);
}
