/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_find_point_slash.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:15:54 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 15:55:54 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include "ft_error.h"
#include <unistd.h>

// checks commands starting by './' in PWD

char	*arg_find_point_slash(char *com, t_pipex_args *p)
{
	char	*result;
	char	*path_val;
	char	*slash_command;
	char	*command;

	result = NULL;
	path_val = arg_val_var(p->pwd);
	if (path_val)
	{
		slash_command = ft_strjoin("/", com);
		command = ft_strjoin(path_val, slash_command);
		p->cmds[p->num_cmds]->is_r = !access(command, R_OK);
		p->cmds[p->num_cmds]->is_x = !access(command, X_OK);
		result = command;
		free(slash_command);
	}
	else
		ft_error_print(ERR006, __func__, __LINE__);
	return (result);
}
