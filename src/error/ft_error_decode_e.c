/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_decode_e.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:36:23 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/28 19:28:14 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

char	*ft_error_decode_e(int e)
{
	if (e == ERR001)
		return ("Environment variable has not char(=)");
	if (e == ERR002)
		return ("Environment variable not found in current environment");
	if (e == ERR003)
		return ("The command does not exits in current path");
	if (e == ERR004)
		return ("PATH variable value has not char(:)");
	return ("Unknow error");
}
