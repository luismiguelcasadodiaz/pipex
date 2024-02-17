/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ejecucion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:33:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/17 09:36:31 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main()
{
	pid_t	PID;
	char *parametros[] = {"ls", "-thal", NULL};

	//Creamos el proceso nuevo
	PID = fork();

	if (PID != -1) // Si no hay error
		if (!PID)  // Si soy el hijo
		{
			execvp("ls", parametros);
			// Si llegamos a esta sentencia...
			//No se ha substituido la imagen del hijo
			puts("Fallo en el proceso hijo\n");
			exit(EXIT_FAILURE);
		}
		else  // Si soy el padre
		{
			printf("%d Padre\n", getpid());
			printf("%d Hijo \n", PID);
		}
	else
		puts("Fallo en el fork\n");
	return (0);
}
