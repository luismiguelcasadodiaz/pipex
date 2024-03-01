/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/01 14:08:04 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	execute(t_pipex_args args)
{
	int	i;

	ft_printf("Execute < %s %s%s ", args.infile, args.cmds[0]->cmd, args.cmds[0]->flg);
	i = 1;
	while (i < (args.max_cmds -1))
	{
		ft_printf("| %s%s ", args.cmds[i]->cmd, args.cmds[i]->flg);
		i++;
	}
	ft_printf("| %s%s > %s\n", args.cmds[args.max_cmds -1]->cmd, args.cmds[args.max_cmds -1]->flg, args.outfile);
}
