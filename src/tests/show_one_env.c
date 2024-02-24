/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_one_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:26:35 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/24 12:25:33 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "argpar.h"
#include <stdio.h>

static char	**de_allocate(char **table, size_t allocated_rows)
{
	while (allocated_rows > 0)
	{
		free(table[--allocated_rows]);
	}
	free(table);
	return (NULL);
}

char	*arg_val_var(char *var)
{
	char	**var_parts;
	char	*result;

	var_parts = ft_split(var, '=');
	if (var_parts)
	{
		result = var_parts[1];
		free(var_parts[0]);
		free(var_parts);
		return (result);
	}
	return (NULL);
}

char	*arg_fin_com(char *var, char *com) 
{
	char	**aux;
	char	**paths;
	char	*var_val;
	char	*command;
	char	*slash_command;
	int		len;
	int		found;

	ft_printf("%s-%s\n", var, com);
	ft_printf("##################\n");
	var_val = arg_val_var(var);
	if (var_val)
	{
	paths = ft_split(var_val, ':');
	slash_command = ft_strjoin("/", com);
	aux = paths;
	len = 0;
	found = 0;
	while(*paths != NULL)
	{	
		command =ft_strjoin(*paths, slash_command);
		if (!found && !access(command, R_OK))
		{
			ft_printf("%s\n", command);
			found = 1;
		}
		free(command);
		paths++;
		len++;
	}
	free(slash_command);
	ft_printf("##################\n");
	aux = de_allocate(aux, len);
	free(var_val);
	return ("Test");
	}
	return (NULL);
}

void	show_usage(void)
{
	ft_printf("./show_one_env <BASH_VARIABLE> <command>\n");
}

int	main(int argc, char **argv)
{
	extern char **environ;
	char		*result;
	char		*command;

	if (argc != 3)
	{
		show_usage();
		return (0);
	}
	result = arg_fin_env_var(environ, argv[1]);
	if (result)
	{
		command = arg_fin_com(result, argv[2]);
		if (command)
			ft_printf("La ruta al comando es %s\n", command);
	}
	return (0);
}
