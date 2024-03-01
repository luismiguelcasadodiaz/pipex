/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_pipex_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:47:06 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/01 13:24:59 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	show_pipex_args(t_pipex_args args)
{
	int	i;

	ft_printf("max_cmds %d\n", args.max_cmds);
	ft_printf("infile %s\n", args.infile);
	ft_printf("outfile %s\n", args.outfile);
	i = -1;
	while (++i < args.max_cmds)
		ft_printf("cmds[%d] %s %s\n", i, args.cmds[i]->cmd, args.cmds[i]->flg);
	ft_printf("all_ok %d\n", args.all_ok);
}
