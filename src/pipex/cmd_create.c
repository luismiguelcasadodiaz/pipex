/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:26:56 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/05 20:42:48 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include "ft_error.h"
#include "libft.h"

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
	r->flg = flg;
	r->ok = KO;
	r->fd_i = -1;
	r->fd_o = -1;
	return (r);
}
