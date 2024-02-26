/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argpar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:21:04 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/26 20:16:17 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGPAR_H
# define ARGPAR_H
# include "pipex.h"

void	show_usage(void);
int		arg_range_int(char *arg, int *my_int);
int		arg_digits(char *arg);
char	*arg_val_var(char *var);
char	*arg_fin_env_var(char **environ, char *var);
int		arg_is_filename(char *arg, char **environ, t_pipex_args *pip_arg);
int		arg_is_command(char *arg, char **environ, t_pipex_args *pip_arg);
int		arg_ok(int argc, char **argv, char **environ, t_pipex_args *pip_arg);
#endif
