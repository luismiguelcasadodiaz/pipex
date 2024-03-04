/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:42:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/04 13:05:39 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argpar.h"
#include "ft_error.h"
#include "ft_printf.h"
#include "libft.h"

/******************************************************************************/
/**
   @file arg_is_command.c
   @brief create_the_command() finds if command com in any of PATH's paths is 
   executable. If it is, returns full path, oterhmise NULL

   @param[in]  var_val: holds the content of PATH variable after '='
   @param[in]      com: the command to locate

   @returns
   A structure with the absolute path to the command, or NULL it not found and
   the text including the command's flags.

   @details
   Checks if there are flags in the command by finding the first whitespace, 
   to isolate the command name and to look for the command executable with
   the help of arg_fin_com().

   ATTENTION HERE. ft_strchr does not allocates memory but ft_substr does.
   ir order to treat equally both variables of t_cmd struct I call ft_strjoin
   that does allocates memory.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
static void	split_cmd(char *var_val, char *arg, char **cmd, char ***flg)
{
	*flg = ft_split(arg, ' ');
	*cmd = arg_fin_com(var_val, *flg[0]);
}
/*	int		arg_len;
	int		flg_len;
	char	*arg_cmd;

	if (!cmd)
		cmd = NULL;
	arg_len = ft_strlen(arg);
	*flg = ft_strchr(arg, ' ');
	if (*flg)
	{
		flg_len = ft_strlen(*flg);
		arg_cmd = ft_substr(arg, 0, arg_len - flg_len);
		*cmd = arg_fin_com(var_val, arg_cmd);
		free(arg_cmd);
	}
	else
	{
		*cmd = arg_fin_com(var_val, arg);
		*flg = "";
	}
	*flg = ft_strjoin(*flg, "");*/

/******************************************************************************/
/**
   @file arg_is_command.c
   @brief arg_is_command() finds if command com in any of PATH's paths is 
   executable. If it is, returns full path, oterhmise NULL

   @param[in]  arg: the pipex argument to verify if its command is executable.
   @param[in]  env: the enviroment where to check.
   @param[out] pip_arg : the pipex structur to keep the executable command wiht
   	the flags

   @returns
   The all_ok flag of the Pipex structure that reports if till now pipex will
   be able to execute the arguments.

   @details
   Find the PATH in the enviroment and gets its value.
   Sets the command inside the pipex structure.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
int	arg_is_command(char *arg, char **env, t_pipex_args *pip_arg)
{
	char	*var_val;
	char	*arg_cmd;
	char	**arg_flags;

	var_val = arg_fin_env_var(env, "PATH");
	if (var_val)
	{
		var_val = arg_val_var(var_val);
		if (!var_val)
			return (-1);
		arg_cmd = NULL;
		arg_flags = NULL;
		split_cmd(var_val, arg, &arg_cmd, &arg_flags);
		set_command(pip_arg, arg_cmd, arg_flags);
		free(var_val);
	}
	return (pip_arg->all_ok);
}
	//show_pipex_args(*pip_arg);
