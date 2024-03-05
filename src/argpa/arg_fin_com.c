/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_fin_com.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:00:28 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/05 20:50:15 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argpar.h"
#include "ft_error.h"
#include <unistd.h>
/******************************************************************************/
/**
   @file arg_fin_com.c
   @brief arg_fin_com() finds if command com in any of PATH's paths is 
   executable. If it is, returns full path, oterhmise NULL

   @param[in]  var_val: holds the content of PATH variable after '='
   @param[in]      com: the command to locate

   @details
   Splits var_val by ':'. 
   Joins to each path the command and test if can access the composition.
   if command is accesible and executable save it as result.
   Frees each invalid path.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
static char	**get_paths(char *path_val)
{
	char	**paths;

	paths = ft_split(path_val, ':');
	if (!paths)
	{
		ft_error_print(ERR004, __func__, __LINE__);
		return (NULL);
	}
	return (paths);
}

char	*arg_fin_com(char *path_val, char *com)
{
	char	**paths;
	char	*command;
	char	*result;
	char	*slash_command;
	int		len;

	slash_command = ft_strjoin("/", com);
	len = 0;
	result = NULL;
	paths = get_paths(path_val);
	while (paths[len] != NULL)
	{
		command = ft_strjoin(paths[len], slash_command);
		if (!result && !access(command, X_OK))
			result = command;
		else
			free(command);
		free(paths[len]);
		len++;
	}
	free(slash_command);
	free(paths);
	return (result);
}
