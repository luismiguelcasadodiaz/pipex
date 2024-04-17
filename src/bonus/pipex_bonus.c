/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:57:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/04/17 13:14:06 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include "ft_error.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	extern char		**environ;
	t_pipex_args	pip_arg;
	int				error_code;

	if (argc >= 5)
	{
		pip_arg = create(argc - 3);
		arg_ok(argc, argv, environ, &pip_arg);
		error_code = execute(pip_arg, environ);
		destroy(pip_arg);
		close(2);
		close(1);
		close(0);
		return (error_code);
	}
	else
		return (EXIT_FAILURE);
}
		//show_pipex_args(pip_arg);
