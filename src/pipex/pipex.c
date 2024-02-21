/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:57:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/21 09:23:19 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "argpar.h"

int	main(int argc, char **argv)
{
	extern char **environ;
	t_pipex_args	pip_arg;

	pip_arg = create();
	if (arg_ok(argc, argv, environ, &pip_arg))
		execute(pip_arg);
	return (0);
}
