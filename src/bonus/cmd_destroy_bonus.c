/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_destroy_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:30:32 by luicasad          #+#    #+#             */
/*   Updated: 2024/04/22 12:05:42 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
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
	x = NULL;
}
