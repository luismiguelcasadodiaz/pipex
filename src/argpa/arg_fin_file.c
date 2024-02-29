/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_fin_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:43:43 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/29 17:25:34 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argpar.h"
#include "ft_error.h"
#include <unistd.h>
#include "pipex.h"
/******************************************************************************/
/**
   @file arg_fin_file.c
   @brief arg_fin_file() finds if filename is in current directory or if it 
   is in some folder relative to PWD. Checks access permission accorgingly
   to data flow direction

   @param[in]  var_val: holds the content of PWD variable after '='
   @param[in]      com: the command to locate

   @details
   Splits var_val by ':'. 
   Joins to each path the command and test if can access the composition.
   if command is accesible and executable save it as result.
   Frees each invalid path.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
char	*arg_fin_file(char *var_val, char *file, int direc)
{
	char	*path;
	char	*result;
	char	*slash_file;
	int		permit;

	if (direc == PIPEX_INPUT)
		permit = R_OK;
	else
		permit = W_OK;
	slash_file = ft_strjoin("/", file);
	result = NULL;
	path = ft_strjoin(var_val, slash_file);
	if (!access(path, permit))
		result = path;
	else
		free(path);
	free(slash_file);
	return (result);
}
