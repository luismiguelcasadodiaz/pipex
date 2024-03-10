/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_fin_com.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:00:28 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/10 01:32:20 by luicasad         ###   ########.fr       */
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


char	*arg_fin_com(char *com, t_pipex_args *p)
{
	char	**paths;
	char	*command;
	char	*result;
	char	*slash_command;
	int		len;
	char	*path_val;

	path_val = arg_val_var(p->path);
	if (path_val)
	{
		result = NULL;
		if (com[0] != '/' && com[0] != '.')
		{
			slash_command = ft_strjoin("/", com);
			len = 0;
			paths = get_paths(path_val);
			while (paths[len] != NULL)
			{
				command = ft_strjoin(paths[len], slash_command);
				if (!result && !access(command, R_OK))
				{
					result = command;
					p->cmds[p->num_cmds]->ok = OK;
					p->cmds[p->num_cmds]->is_X = !access(command, X_OK);
				}
				else
					free(command);
				free(paths[len]);
				len++;
			}
			free(slash_command);
			free(paths);
		}
		else
		{
			if (!access(com, R_OK))
				{
					result = com;
					p->cmds[p->num_cmds]->ok = OK;
					p->cmds[p->num_cmds]->is_X = !access(com, X_OK);
				}
				result = com;
		}
	}
	return (result);
}
