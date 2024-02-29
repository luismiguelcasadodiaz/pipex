/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:29:00 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/29 13:55:40 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_error.h"
#include <stdlib.h>

/******************************************************************************/
/**
   @file set_command.c
   @brief set_commnad() assigns the verified absolute path to the current slot
   and apdate the all_ok status variable.

   @param[in]  pip_arg: the t_pipex_arg variable to update
   @param[in]  command: the verified accessible absolute path to command

   @details
   assigns to the current availableoops the stack couting how many values
   are lower or equal than current (external loop node) node's value.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
void	set_command(t_pipex_args *pip_arg, char *command)
{
	if (pip_arg->num_cmds < pip_arg->max_cmds)
	{
		pip_arg->cmds[pip_arg->num_cmds++] = command;
		pip_arg->all_ok = pip_arg->all_ok && (command != NULL);
		if (!command)
			ft_error_print(ERR003, __func__, __LINE__);
	}
	else
		ft_error_print(ERR050, __func__, __LINE__);
}