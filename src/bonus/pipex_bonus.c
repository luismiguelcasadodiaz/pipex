/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:57:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/20 12:26:40 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include "ft_error.h"

int	main(int argc, char **argv)
{
	extern char		**environ;
	t_pipex_args	pip_arg;

	if (argc >= 5)
	{
		pip_arg = create(argc - 3);
		arg_ok(argc, argv, environ, &pip_arg);
		//show_pipex_args(pip_arg);
		execute(pip_arg, environ);
		destroy(pip_arg);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
	close(2);
	close(1);
	close(0);
}
		//show_pipex_args(pip_arg);
