/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ejecucion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:33:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/04 17:51:11 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	pid_t	pid;
	char	*parametros[] = {"ls", "-thal", NULL};

	pid = fork();
	if (pid != -1)
		if (!pid)
		{
			execvp("ls", parametros);
			puts("Fallo en el proceso hijo\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("%d Padre\n", getpid());
			printf("%d Hijo \n", pid);
		}
	else
		puts("Fallo en el fork\n");
	return (0);
}
