/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:13:08 by luicasad          #+#    #+#             */
/*   Updated: 2023/12/10 08:54:19 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifdef __linux__
#  define MY_SYMBOL 1
#  define MY_ULL_MAX ULLONG_MAX
# elif __APPLE__
#  define MY_SYMBOL 2
#  define MY_ULL_MAX ULONG_LONG_MAX
# endif

# define FD 1

ssize_t	ft_write_c(char c);
ssize_t	ft_write_str(char *str);
ssize_t	ft_write_int_base(int num, int base, char *basechars, ssize_t *digits);
ssize_t	ft_write_uns_base(unsigned long long n,
			unsigned long long b,
			char *c,
			ssize_t *d);
ssize_t	ft_write_dec(int num);
ssize_t	ft_write_int(int num);
ssize_t	ft_write_ptr(void *num);
ssize_t	ft_write_uns(unsigned int num);
ssize_t	ft_write_hex_low(unsigned int num);
ssize_t	ft_write_hex_cap(unsigned int num);
int		ft_printf(const char *fmt, ...);
//int	ft_printf(const char *fmt, ...)__attribute__((format (printf, 1, 2)));
#endif
/* ************************************************************************** */
/* A function suffix like "__attribute__((format (printf, 1, 2)))" instruct   */
/* the compiler to check inconsistencies between variable arguments and the   */
/* format instrunction.                                                       */
/* ************************************************************************** */
