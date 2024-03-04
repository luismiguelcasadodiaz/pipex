/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envi_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:26:35 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/20 15:38:40 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv)
{
	extern char **environ;
	int n;

	n = 0;
	while (*environ != NULL)
	{
		printf("%s\n", *environ);
		environ++;
	}
}

