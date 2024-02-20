/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/20 18:59:54 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	execute(t_pipex_args args)
{
	ft_printf("Execute < %s %s | %s > %s\n", args.infile, args.cmd1, args.cmd2, args.outfile); 
}
