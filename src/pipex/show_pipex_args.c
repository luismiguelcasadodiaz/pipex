/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_pipex_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:47:06 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/20 18:52:22 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	show_pipex_args(t_pipex_args args)
{
		ft_printf("infile %s\n", args.infile);
		ft_printf("outfile %s\n", args.outfile);
		ft_printf("cmd1 %s\n", args.cmd1);
		ft_printf("cmd2 %s\n", args.cmd2);
}
