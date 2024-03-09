/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:52:55 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/09 13:29:15 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

enum e_my_errors
{
	ERR001 = -1,
	ERR002 = -2,
	ERR003 = -3,
	ERR004 = -4,
	ERR005 = -5,
	ERR006 = -6,
	ERR007 = -7,
	ERR008 = -8,
	ERR010 = -10,
	ERR020 = -20,
	ERR021 = -21,
	ERR050 = -50,
	ERR051 = -51,
	ERR126 = -126,
	ERR127 = -127,
	ERRnnn = -999
};

char	*ft_error_str(int e);
char	*ft_error_decode_e(int e);
void	ft_error_print(int e, const char *f, int l);
char	*ft_error_text(int e, const char *f, int l);
void	ft_error_exit(int e, const char *f, int l);
#endif
