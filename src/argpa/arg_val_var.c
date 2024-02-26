/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_val_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:01:50 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/26 20:16:18 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/******************************************************************************/
/**
   @file arg_val_var.c
   @brief arg_val_var() returns the text after '=' from an enviromental var

   @param[in]  *vars: an enviromental variable wiht this format:
            NAME=VALUE

   @details
   Split the variable definition by char '='.  stack couting how many values
   are lower or equal than current (external loop node) node's value.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
char	*arg_val_var(char *var)
{
	char	**var_parts;
	char	*result;

	var_parts = ft_split(var, '=');
	if (var_parts)
	{
		result = var_parts[1];
		free(var_parts[0]);
		free(var_parts);
		return (result);
	}
	return (NULL);
}
