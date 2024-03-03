/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:56:34 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/02 11:08:14 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argpar.h"
#include "pipex.h"

/* ************************************************************************** */
/*.<*                                                                        .*/
/*.@file arg_pars.c                                                          .*/
/*.@brief arg_ok()i if arguments as unique integers that pushes into stacks. .*/
/*.                                                                          .*/
/*.@param[in] argc: number of arguments to verify.          .                .*/
/*.@param[in] argv: table  of arguments to verifi .                          .*/
/*.                                                                          .*/
/*.@returns a stack with first argument on the top when all arguments are    .*/
/*.  ok. Otherwise returns NULL.                                             .*/
/*.                                                                          .*/
/*.@details                                                                  .*/
/*.Creates a stack 'c' to keep the arguments                                 .*/
/*.                                                                          .*/
/*.Set the hypothesis all arguments are ok (all_ok = 1)                      .*/
/*.                                                                          .*/
/*.Loops over the table of arguments verifing requirements:                  .*/
/*. 1.- The argument represents an integer.                                  .*/
/*. 2.- The integer fits in a  "int" type.                                   .*/
/*. 3.- The integer is not in the stack.                                     .*/
/*.                                                                          .*/
/*. if the argument satisfy all 3 requirements, it is pushed into the stack. .*/
/*.                                                                          .*/
/*.After processing all the table, if all arguments passed requirements,     .*/
/*.the arguments order in the stack is reversed to have first argument on    .*/
/*.stack's top and returns it. Otherwise returns NULL                        .*/
/*.                                                                          .*/
/*./author LMCD (Luis Miguel Casado Diaz)                                    .*/
/*.>*                                                                        .*/
/* ************************************************************************** */
int	arg_ok(int argc, char **argv, char **environ, t_pipex_args *pip_arg)
{
	int	all_ok;
	int	i;

	all_ok = 1;
	all_ok = all_ok && \
			arg_is_filename(argv[1], environ, pip_arg, PIPEX_INPUT);
	if (!all_ok)
		return (0);
	i = 2;
	while (i < argc - 1)
	{
		all_ok = all_ok && arg_is_command(argv[i++], environ, pip_arg);
		if (!all_ok)
			return (0);
	}
	all_ok = all_ok && \
			arg_is_filename(argv[argc - 1], environ, pip_arg, PIPEX_OUTPUT);
	if (!all_ok)
		return (0);
	return (all_ok);
}
