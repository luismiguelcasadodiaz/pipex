/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/29 16:06:08 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	execute(t_pipex_args args)
{
	int	i;

	ft_printf("Execute < %s %s ", args.infile, args.cmds[0]);
	i = 1;
	while (i < (args.max_cmds -1))
	{
		ft_printf("| %s ", args.cmds[i]);
		i++;
	}
	ft_printf("| %s > %s\n", args.cmds[args.max_cmds -1], args.outfile);
}
