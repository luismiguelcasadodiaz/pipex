/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:57:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/03 21:48:55 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "argpar.h"

int	main(int argc, char **argv)
{
	extern char		**environ;
	t_pipex_args	pip_arg;

	if (argc >= 5)
	{
		pip_arg = create(argc - 3);
		if (arg_ok(argc, argv, environ, &pip_arg))
			execute(pip_arg, environ);
		destroy(pip_arg);
	}
	else
		show_usage();
	return (0);
}
