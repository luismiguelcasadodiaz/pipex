/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:52:55 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/27 12:31:35 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

enum e_my_errors
{
ERR001 = -1,
ERR002 = -2,
ERR003 = -3,
ERRnnn = -999
};

char	*ft_error_str(int e);
char	*ft_error_decode_e(int e);
void	ft_error_print(int e, const char *f, int l);
#endif
