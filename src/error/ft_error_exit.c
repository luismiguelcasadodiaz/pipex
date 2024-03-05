/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:11:01 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/05 11:44:45 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include <stdlib.h>

void	ft_error_exit(int e, const char *f, int l)
{
	ft_error_print(e, f, l);
	exit(-1 * e);
}
