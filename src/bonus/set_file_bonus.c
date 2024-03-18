/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:25:34 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/02 12:29:03 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_error.h"
#include <stdlib.h>

/******************************************************************************/
/**
   @file set_file.c
   @brief set_file() assigns the verified absolute path to the correct pointer
   and update the all_ok status variable.

   @param[in]  pip_arg: the t_pipex_arg variable to update
   @param[in]  filename: the verified accessible absolute path to filename
   @param[in]     direc: Flags if deals with an input or an output file.

   @details
   assigns to the current availableoops the stack couting how many values
   are lower or equal than current (external loop node) node's value.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
void	set_file(t_pipex_args *pip_arg, char *filename, int direc)
{
	if (direc == PIPEX_INPUT)
		pip_arg->infile = filename;
	else
		pip_arg->outfile = filename;
	pip_arg->all_ok = pip_arg->all_ok && (filename != NULL);
	if (!filename)
		ft_error_print(ERR006, __func__, __LINE__);
}
