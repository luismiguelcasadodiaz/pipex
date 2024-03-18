/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:42:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 15:51:25 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "ft_error.h"
#include "ft_printf.h"
#include "libft.h"

/******************************************************************************/
/**
   @file arg_is_command.c
   @brief arg_is_command() finds if command com in any of PATH's paths is 
   executable. If it is, returns full path, oterhmise NULL

   @param[in]  arg: the pipex argument to verify if its command is executable.
   @param[out] pip_arg : the pipex structur to keep the executable command wiht
   	the flags

   @returns
   The all_ok flag of the Pipex structure that reports if till now pipex will
   be able to execute the arguments.

   @details
   Find the PATH in the enviroment and gets its value.
   Sets the command inside the pipex structure.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
void	arg_is_command(char *arg, t_pipex_args *pip_arg)
{
	char	*arg_cmd;
	char	**arg_flags;

	arg_flags = ft_split_pipex(arg, ' ');
	arg_cmd = arg_fin_com(arg_flags[0], pip_arg);
	if (pip_arg->num_cmds < pip_arg->max_cmds)
	{
		pip_arg->cmds[pip_arg->num_cmds]->cmd = arg_cmd;
		pip_arg->cmds[pip_arg->num_cmds]->cli = arg_flags[0];
		pip_arg->cmds[pip_arg->num_cmds++]->flg = arg_flags;
		pip_arg->all_ok = pip_arg->all_ok && \
						pip_arg->cmds[pip_arg->num_cmds]->is_r && \
						pip_arg->cmds[pip_arg->num_cmds]->is_x;
	}
	else
		ft_error_print(ERR050, __func__, __LINE__);
}
	//show_pipex_args(*pip_arg);	
