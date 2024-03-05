/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:56:34 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/05 11:12:04 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argpar.h"
#include "pipex.h"

/* ************************************************************************** */
/*.<*                                                                        .*/
/*.@file arg_pars.c                                                          .*/
/*.@brief arg_ok() checks if pipex arguments are accesible or executable   . .*/
/*.                                                                          .*/
/*.@param[in] argc: number of arguments to verify.          .                .*/
/*.@param[in] argv: table  of arguments to verify .                          .*/
/*.@param[in] environ: environment to find PAHT and PWD variables            .*/
/*.@param[in] pip_arg: struct that keep checking result                      .*/
/*.                                                                          .*/
/*.@returns all_ok that reports with 1 that all arguments are accesible or   .*/
/*.  ejecutable- Otherwise retunrs 0.                                        .*/
/*.                                                                          .*/
/*.@details                                                                  .*/
/*.                                                                          .*/
/*.Set the hypothesis all arguments are ok (all_ok = 1)                      .*/
/*.                                                                          .*/
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
			arg_is_in_file(argv[1], environ, pip_arg);
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
			arg_is_ou_file(argv[argc - 1], environ, pip_arg);
	if (!all_ok)
		return (0);
	return (all_ok);
}
