/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ejecucion_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:32:53 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/14 18:42:55 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	int	result;

	//test is a shell exist
	if (system(NULL))
		puts("Hay disponible un porcesador de comandos\n");
	else
	{
		puts("No hay disponible un procesador de comandos\n");
		exit (-1);
	}
	//Ejecutamos el comando fecha
	if ((result = system("data")) == -1)
		puts("Fallo en la creación del proceso\n");
	else
		printf("Valor de retorno: %d\n", result);
	return (0);
}
