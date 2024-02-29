/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:37:38 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/29 17:15:07 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argpar.h"
#include "ft_printf.h"

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
