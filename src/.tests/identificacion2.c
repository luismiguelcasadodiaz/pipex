/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identificacion2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:12:53 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/16 00:17:04 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void	proceso_padre()
{
	int n;

	// Imprimir los numeros pares del 0 al 10
	n = -1;
	while (++n <=10)
		if ((n % 2) == 0)
			printf("Padre %d\n", n);
}

void	proceso_hijo()
{
	int n;

	// Imprimir los numeros impares del 0 al 10
	n = -1;
	while (++n <=10)
		if ((n % 2) != 0)
			printf("Hijo \t%d\n", n);
}

int	main(void)
{
	pid_t	pid_son;
	
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

	// una pequeña espera para que se vista el hijo
	sleep(1);

	if (pid_son == 0)
		proceso_hijo();
	else
		proceso_padre();
	return (0);
}
