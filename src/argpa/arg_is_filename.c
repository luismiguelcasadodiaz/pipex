/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:37:38 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/02 12:25:09 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argpar.h"
#include "ft_printf.h"

/******************************************************************************/
/**
   @file arg_is_filename.c
   @brief arg_is_filename() finds filename and checks access permission.

   @param[in]  arg: the pipex argument to verify if its command is executable.
   @param[in]  env: the enviroment where to check.
   @param[out] pip_arg : the pipex structur to keep the executable command wiht
   	the flags
   @param[in]  direc: the direction the data flows (read/write)

   @returns
   The all_ok flag of the Pipex structure that reports if till now pipex will
   be able to execute the arguments.

   @details
   Find the PWD in the enviroment and gets its value.
   verifies wiht the help of arg_fin_file() if filename exists and if has the
   right access permission.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
int	arg_is_filename(char *arg, char **env, t_pipex_args *pip_arg, int direc)
{
	char	*var;
	char	*var_val;
	char	*path;

	var = arg_fin_env_var(env, "PWD");
	if (var)
	{
		var_val = arg_val_var(var);
		if (!var_val)
			return (-1);
		path = arg_fin_file(var_val, arg, direc);
		free(var_val);
		set_file(pip_arg, path, direc);
	}
	show_pipex_args(*pip_arg);
	return (pip_arg->all_ok);
}
