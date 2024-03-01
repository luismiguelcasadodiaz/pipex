/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:42:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/01 14:02:45 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argpar.h"
#include "ft_error.h"
#include "ft_printf.h"
#include "libft.h"
void	split_cmd_flags(char *arg, char **cmd, char **flags)
{
	char	*first_blank;
	int		arg_len;
	int		idx_blank;

	arg_len = ft_strlen(arg);
	first_blank = ft_strchr(arg, ' ');
	if (first_blank)
	{
		idx_blank = &first_blank - &arg -2;
		*cmd = ft_substr(arg, 0, idx_blank);
		*flags = ft_substr(arg, idx_blank, arg_len);
	}
	else
	{
		*cmd = arg; 
		*flags = "";
	}
}

int	arg_is_command(char *arg, char **environ, t_pipex_args *pip_arg)
{
	char	*var;
	char	*var_val;
	char	*arg_cmd;
	char	*arg_flags;
	t_cmd	command;

	arg_cmd = NULL;
	arg_flags = NULL;
	command = cmd_create(NULL, NULL);
	split_cmd_flags(arg, &arg_cmd, &arg_flags);
	var = arg_fin_env_var(environ, "PATH");
	if (var)
	{
		var_val = arg_val_var(var);
		if (!var_val)
			return (-1);
		command.cmd = arg_fin_com(var_val, arg_cmd);
		command.flg = arg_flags;
		free(var_val);
		set_command(pip_arg, &command);
	}
	show_pipex_args(*pip_arg);
	return (pip_arg->all_ok);
}
