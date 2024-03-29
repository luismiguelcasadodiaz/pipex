/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_pipex_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:47:06 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/11 15:28:22 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	show_pipex_args(t_pipex_args args)
{
	int	i;
	int	j;

	ft_printf("max_cmds %d\n", args.max_cmds);
	ft_printf("infile %s\n", args.infile);
	ft_printf("outfile %s\n", args.outfile);
	i = -1;
	while (++i < args.max_cmds)
	{
		ft_printf("cli %s --> cmds[%d] %s ", \
				args.cmds[i]->cli, i, args.cmds[i]->cmd);
		if (args.cmds[i]->flg)
		{
			j = 1;
			while (args.cmds[i]->flg[j] != NULL)
				ft_printf("%s ", args.cmds[i]->flg[j++]);
		}
		ft_printf("fd_i=%d ", args.cmds[i]->fd_i);
		ft_printf("fd_o=%d ", args.cmds[i]->fd_o);
		ft_printf("R_OK=%d ", args.cmds[i]->ok);
		ft_printf("X_OK=%d ", args.cmds[i]->is_x);
		ft_printf("\n");
	}
	ft_printf("all_ok %d\n", args.all_ok);
}
