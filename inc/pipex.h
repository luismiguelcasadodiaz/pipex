/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:51:53 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/21 09:17:57 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

typedef struct	s_pipex_args
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
}	t_pipex_args;

t_pipex_args	create();
void			execute(t_pipex_args pip_arg);
void			show_pipex_args(t_pipex_args args);
#endif
