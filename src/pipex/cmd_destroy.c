/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:30:32 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 14:18:53 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "unistd.h"
#include <stdlib.h>

void	cmd_destroy(t_cmd *x)
{
	int	i;

	i = 0;
	while (x->flg[i] != NULL)
		free(x->flg[i++]);
	if (x->is_r)
		free(x->cmd);
	free(x->flg);
	if (x->fd_i != -1)
		close(x->fd_i);
	if (x->fd_o != -1)
		close(x->fd_o);
	x = NULL;
}
