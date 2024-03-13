/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_fin_com.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:00:28 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/11 17:46:28 by luicasad         ###   ########.fr       */
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

// checks commands starting by '/'
static char	*find_slash(char *com, t_pipex_args *p)
{
	p->cmds[p->num_cmds]->ok = !access(com, R_OK);
	p->cmds[p->num_cmds]->is_x = !access(com, X_OK);
	if (p->cmds[p->num_cmds]->ok)
		return (com);
	else
		return (NULL);
}

static void	my_help(char *com, t_pipex_args *p, char **result, char *path_val)
{
	char	**paths;
	char	*command;
	char	*slash_command;
	int		len;

	slash_command = ft_strjoin("/", com);
	len = 0;
	paths = get_paths(path_val);
	while (paths[len] != NULL)
	{
		command = ft_strjoin(paths[len], slash_command);
		if (!(*result) && !access(command, R_OK))
		{
			*result = command;
			p->cmds[p->num_cmds]->ok = OK;
			p->cmds[p->num_cmds]->is_x = !access(command, X_OK);
		}
		else
			free(command);
		free(paths[len]);
		len++;
	}
	free(slash_command);
	free(paths);
	free(path_val);
}

// checks commands starting by any character in PATH 
static char	*find_file_in_path(char *com, t_pipex_args *p)
{
	char	*result;
	char	*path_val;

	result = NULL;
	path_val = arg_val_var(p->path);
	if (path_val)
		my_help(com, p, &result, path_val);
	else
		ft_error_print(ERR006, __func__, __LINE__);
	return (result);
}

char	*arg_fin_com(char *com, t_pipex_args *p)
{
	char	*result;

	result = NULL;
	if (com[0] == '.')
		result = arg_find_point_slash(com, p);
	else if (com[0] == '/')
		result = find_slash(com, p);
	else
		result = find_file_in_path(com, p);
	return (result);
}
