/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creaproceso.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:12:53 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/14 19:31:33 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	pid_t	pid_son;
	int		n;
	
	// Creamos el nuevo proceso
	pid_son = fork();

	// A partir de este punto hay dos procesos separados.
	// Se ejecutan independientemente.
	// Ejecutan duplicadamente las siguientes sentencias

	if (pid_son == -1)
	{
		puts("Fallo al crear el proceso\n");
		exit (-1);
	}

	// bucle contador 0 .. 10
	n = 0;
	while (n++ < 10)
	{
		printf("%s- %d N=%d\n",(pid_son == 0) ? "hijo": "padre", pid_son, n);
		sleep(rand() % 3);
	}
	return (0);
}

/*

== output wihtout sleep ==
padre- 12494 N=1
padre- 12494 N=2
padre- 12494 N=3
padre- 12494 N=4
padre- 12494 N=5
padre- 12494 N=6
padre- 12494 N=7
padre- 12494 N=8
padre- 12494 N=9
padre- 12494 N=10
hijo- 0 N=1
hijo- 0 N=2
hijo- 0 N=3
hijo- 0 N=4
hijo- 0 N=5
hijo- 0 N=6
hijo- 0 N=7
hijo- 0 N=8
hijo- 0 N=9
hijo- 0 N=10

== with sleep ==
padre- 12523 N=1
hijo- 0 N=1
padre- 12523 N=2
hijo- 0 N=2
padre- 12523 N=3
padre- 12523 N=4
hijo- 0 N=3
hijo- 0 N=4
padre- 12523 N=5
hijo- 0 N=5
padre- 12523 N=6
hijo- 0 N=6
padre- 12523 N=7
hijo- 0 N=7
padre- 12523 N=8
hijo- 0 N=8
padre- 12523 N=9
hijo- 0 N=9
padre- 12523 N=10
hijo- 0 N=10

*/
