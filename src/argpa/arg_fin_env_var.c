/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_fin_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:11:01 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/29 16:04:15 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_error.h"

/******************************************************************************/
/**
   @file arg_fin_env_var.c
   @brief arg_fin_env_var() finds a variable in an environment

   @param[in] environs: a **char variable with all enviromental variables
   @param[in] var: The variable name to look for

   @details
   Loops the environment. For each var check if var name appears in it.        
   When match returns the pointer to found variable, Otherwise returns NULL

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
char	*arg_fin_env_var(char **environ, char	*var)
{
	int		len;
	char	*result;

	len = ft_strlen(var);
	while (*environ != NULL)
	{
		result = ft_strnstr(*environ, var, len);
		if (result)
			return (*environ);
		environ++;
	}
	ft_error_print(ERR002, __func__, __LINE__);
	return (NULL);
}
