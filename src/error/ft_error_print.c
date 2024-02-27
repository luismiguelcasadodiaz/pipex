/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:43:45 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/27 12:34:41 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_error.h"
#include <stdio.h>

void	ft_error_print(int e, const char *f, int l)
{
	char	*linn;
	char	*func;
	char	*line;
	char	*loca;
	char	*text;

	linn = ft_itoa(l);
	func = ft_strjoin(f, ":");
	line = ft_strjoin(linn, "-> ");
	loca = ft_strjoin(func, line);
	text = ft_strjoin(loca, ft_error_str(e));
	perror(text);
	free(linn);
	free(func);
	free(line);
	free(loca);
	free(text);
}
