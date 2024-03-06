/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:57:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/06 20:19:32 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "argpar.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	extern char		**environ;
	t_pipex_args	pip_arg;

	if (argc == 5)
	{
		pip_arg = create(argc - 3);
		arg_ok(argc, argv, environ, &pip_arg);
		execute(pip_arg, environ);
		destroy(pip_arg);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
