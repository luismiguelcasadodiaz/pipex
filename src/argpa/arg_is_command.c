/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:42:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/20 18:58:48 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argpar.h"
#include "ft_printf.h"

int		arg_is_command(char *arg, char **environ, t_pipex_args *pip_arg)
{
		ft_printf("is %s a command? %s \n", arg, environ[1]);
		show_pipex_args(*pip_arg);
		return (1);
}
