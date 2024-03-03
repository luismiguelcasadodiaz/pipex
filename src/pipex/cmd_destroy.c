/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:30:32 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/03 19:15:55 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

void	cmd_destroy(t_cmd *x)
{
	int	i;

	free(x->cmd);
	i = 0;
	while (x->flg[i] != NULL)
		free(x->flg[i++]);
	free(x->flg[i]);
	free(x->flg);
	x = NULL;
}
