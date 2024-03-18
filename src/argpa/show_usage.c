/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:19:38 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 13:36:46 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	show_usage(void)
{
	ft_printf("USAGE:./pipex <file1> <cmd1> <cmd2> <file2>\n");
	ft_printf("NOTE:<file1> a correct filename with read permit.\n");
	ft_printf("NOTE:<file2> a correct filename with write permit.\n");
	ft_printf("NOTE:<cmd>  are shell commands.\n");
	ft_printf("NOTE:if <cmd> has flags use quotation marks.\n");
	return ;
}
