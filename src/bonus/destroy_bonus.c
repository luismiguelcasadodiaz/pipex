/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:38:36 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 12:37:02 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>

void	destroy(t_pipex_args args)
{
	int	i;

	if (args.free_infile)
		free(args.infile);
	if (args.free_outfile)
		free(args.outfile);
	i = args.max_cmds;
	while (--i >= 0)
	{
		cmd_destroy(args.cmds[i]);
		free(args.cmds[i]);
	}
	free(args.cmds);
	args.cmds = NULL;
}
