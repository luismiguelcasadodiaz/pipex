/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:26:35 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/20 15:34:00 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int n;

	n = 0;
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

