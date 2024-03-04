/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_one_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:26:35 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/28 22:29:45 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "argpar.h"
#include "ft_error.h"
#include <stdio.h>

void	show_usage(void)
{
	ft_printf("./show_one_env <BASH_VARIABLE> <command>\n");
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	char		*var;
	char		*var_val;
	char		*command;

	if (argc != 3)
	{
		show_usage();
		return (0);
	}
	var = arg_fin_env_var(environ, argv[1]);
	if (var)
	{
		var_val = arg_val_var(var);
		if (!var_val)
			return (-1);
		command = arg_fin_com(var_val, argv[2]);
		free(var_val);
		if (command)
			ft_printf("La ruta al comando es %s\n", command);
		else
			ft_error_print(ERR003, __func__, __LINE__);
		free(command);
	}
	return (0);
}
