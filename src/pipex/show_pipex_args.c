/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_pipex_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:47:06 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/04 13:37:18 by luicasad         ###   ########.fr       */
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
		ft_printf("cmds[%d] %s ", i, args.cmds[i]->cmd);
		if (args.cmds[i]->flg)
		{
			j = 1;
			while (args.cmds[i]->flg[j] != NULL)
				ft_printf("%s ", args.cmds[i]->flg[j++]);
		}
		ft_printf("\n");
	}
	ft_printf("all_ok %d\n", args.all_ok);
}
