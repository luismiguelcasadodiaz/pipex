/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_fin_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:43:43 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/04 22:11:32 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argpar.h"
#include "ft_error.h"
#include <unistd.h>
#include "pipex.h"
/******************************************************************************/
/**
   @file arg_fin_file.c
   @brief arg_fin_file() finds if filename is in current directory or if it 
   is in some folder relative to PWD. Checks access permission accorgingly
   to data flow direction

   @param[in]  var_val: holds the content of PWD variable after '='
   @param[in]     file: the file to locate

   @details
   Joins to PWD "/file".
   Make the hypothesys that the file has not access permision so returns NULL.
   for infile checks it is readable.
   for outfile checks it is writable

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
char	*arg_fin_file(char *var_val, char *file, int direc)
{
	char	*path;
	char	*result;
	char	*slash_file;

	slash_file = ft_strjoin("/", file);
	path = ft_strjoin(var_val, slash_file);
	result = NULL;
	if ((direc == PIPEX_INPUT) && !access(path, R_OK))
		result = path;
	else if ((direc == PIPEX_OUTPUT) && !access(path, W_OK))
		result = path;
	else if ((direc == PIPEX_OUTPUT) && access(path, F_OK))
		result = path;
	else
		free(path);
	/*if (direc == PIPEX_INPUT)
		permit = R_OK;
	else
		permit = W_OK;
	if (!access(path, permit))
		result = path;
	else
		free(path);
	*/
	free(slash_file);
	return (result);
}
