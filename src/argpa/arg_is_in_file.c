/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_in_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:37:38 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/11 14:05:05 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argpar.h"
#include "pipex.h"
#include "ft_error.h"
#include <unistd.h>

/******************************************************************************/
/**
   @file arg_is_in_file.c
   @brief arg_is_in_file() finds filename and checks access permission.

   @param[in]  arg: the pipex argument to verify if it is an accessible file
   @param[in]  env: the enviroment where to check.
   @param[out] pip_arg : the pipex structure to keep the file name path

   @returns
   The all_ok flag of the Pipex structure that reports if till now pipex will
   be able to execute the arguments.

   @details
   Find the PWD in the enviroment and gets its value.
   If the file does not exists or has not read permit, Exits
   assing path to infile to the pipex struct

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
void	arg_is_in_file(char *file, t_pipex_args *pip_arg)
{
	char	*pwd_val;
	char	*file_path;
	char	*slash_file;

	pip_arg->infile = NULL;
	pwd_val = arg_val_var(pip_arg->pwd);
	if (pwd_val)
	{
		if (file[0] != '/')
		{
			slash_file = ft_strjoin("/", file);
			file_path = ft_strjoin(pwd_val, slash_file);
			free(pwd_val);
			free(slash_file);
			pip_arg->free_infile = 1;
		}
		else
			file_path = file;
		pip_arg->infile = file_path;
		pip_arg->in_arg = file;
		pip_arg->all_ok = pip_arg->all_ok && (pip_arg->infile != NULL);
	}
}
		//if (access(file_path, F_OK))
		//	ft_error_print(errno, __func__, __LINE__);
		//if (access(file_path, R_OK))
		//	ft_error_print(errno, __func__, __LINE__);
		//show_pipex_args(*pip_arg);
