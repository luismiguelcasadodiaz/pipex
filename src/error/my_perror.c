/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:42:11 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 11:53:14 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>

void	my_perror(char *a, char *b)
{
	char	*j;
	char	*i;

	if (b)
	{
		j = ft_strjoin(a, b);
		i = ft_strjoin("pipex: ", j);
		ft_printf("%s\n", i);
		free(j);
		free(i);
	}
	else
	{
		j = ft_strjoin("pipex: ", a);
		perror(j);
		free(j);
	}
}
