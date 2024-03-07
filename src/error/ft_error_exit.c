/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:11:01 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/07 20:34:36 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include <stdlib.h>


// my range of errors is negative. i positivize them multiplying by -1
void	ft_error_exit(int e, const char *f, int l)
{
	ft_error_print(e, f, l);
	//if (ERRnnn <= e && e <= ERR001)
	//	exit(-1 * e);
	//else
	//	exit(e);
	exit(EXIT_FAILURE);
}
