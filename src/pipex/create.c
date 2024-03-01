/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:18:22 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/01 13:45:26 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include "ft_error.h"

t_pipex_args	create(int max_cmds)
{
	t_pipex_args	r;
	int				i;

	r.max_cmds = max_cmds;
	r.num_cmds = 0;
	r.infile = NULL;
	r.outfile = NULL;
	r.cmds = (t_cmd **) malloc(max_cmds * sizeof(t_cmd *));
	if (!r.cmds)
	{
		ft_error_print(ERR005, __func__, __LINE__);
		exit(-1);
	}
	i = -1;
	while (++i < r.max_cmds)
	{
		r.cmds[i] = (t_cmd *) malloc(sizeof(t_cmd));
		if (!r.cmds[i])
		{
			ft_error_print(ERR005, __func__, __LINE__);
			exit(-1);
		}
		r.cmds[i]->cmd = NULL;
		r.cmds[i]->flg = NULL;
	}
	r.all_ok = 1;
	return (r);
}
