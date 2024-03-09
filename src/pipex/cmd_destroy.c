/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:30:32 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/09 15:57:27 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "unistd.h"
#include <stdlib.h>

void	cmd_destroy(t_cmd *x)
{
	int	i;

	if (x->ok)
	{
		free(x->cmd);
		free(x->cli);
	}
	i = 0;
	while (x->flg[i] != NULL)
		free(x->flg[i++]);
	free(x->flg[i]);
	free(x->flg);
	close(x->fd_i);
	close(x->fd_o);
	x = NULL;
}
