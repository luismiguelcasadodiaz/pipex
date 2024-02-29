/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:38:36 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/29 17:27:53 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

void	destroy(t_pipex_args args)
{
	int	i;

	free(args.infile);
	free(args.outfile);
	i = args.max_cmds;
	while (--i >= 0)
		free(args.cmds[i]);
	free(args.cmds);
	args.cmds = NULL;
}
