/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:26:56 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 14:22:00 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>
#include "ft_error.h"
#include "libft.h"
#include <unistd.h>

t_cmd	*cmd_create(char *cmd, char **flg)
{
	t_cmd	*r;

	r = (t_cmd *) malloc(sizeof(t_cmd));
	if (!r)
	{
		ft_error_print(ERR005, __func__, __LINE__);
		exit(-1);
	}
	r->cmd = cmd;
	r->cli = cmd;
	r->flg = flg;
	r->is_r = KO;
	r->is_x = 0;
	r->fd_i = -1;
	r->fd_o = -1;
	if (pipe(r->pfd) < 0)
		ft_error_exit(ERR021, __func__, __LINE__);
	return (r);
}
