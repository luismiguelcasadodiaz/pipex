/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:42:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/29 16:04:28 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argpar.h"
#include "ft_error.h"
#include "ft_printf.h"

int	arg_is_command(char *arg, char **environ, t_pipex_args *pip_arg)
{
	char	*var;
	char	*var_val;
	char	*command;

	var = arg_fin_env_var(environ, "PATH");
	if (var)
	{
		var_val = arg_val_var(var);
		if (!var_val)
			return (-1);
		command = arg_fin_com(var_val, arg);
		free(var_val);
		set_command(pip_arg, command);
	}
	show_pipex_args(*pip_arg);
	return (pip_arg->all_ok);
}
