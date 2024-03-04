/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuberias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:25:51 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/20 11:35:40 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LENGTH 256

int	padre_hijo[2];
int	hijo_padre[2];

void	proceso_padre(void)
{
	FILE	*entrada;
	FILE	*salida;
	char	resultado[MAX_LENGTH];

	puts("-- Padre: Empiezo --\n");

	//Cerramos los descriptores de archivo no usados
	close(padre_hijo[0]);
	close(hijo_padre[1]);

	//identificamos los descriptores que usará el padre
	printf("-- Padre: Descriptores (%d, %d) --\n",
		hijo_padre[0], padre_hijo[1]);

	// Abrimos la salida hacia el hijo
	salida = fdopen(padre_hijo[1], "w");
	if (!salida)
	{
		puts("-- Padre: Fallo en la apertura --\n");
		return ;
	}

	//La tuberia está preparada
	puts("-- Padre: Tuberias preparadas\n");

	//Enviamos el dato que debe operar el hijo
	if (fputs("24", salida) == EOF)
	{
		puts("-- Padre: Fallo al escribir --\n");
		return ;
	}
	// y cerramos 
	fclose(salida);
	puts("-- Padre: Envido el dato --\n");

	// Abrimos la tubería para recoger el dato del hijo
	entrada = fdopen(hijo_padre[0], "r");

	//Leemos el resultado
	fgets(resultado, MAX_LENGTH, entrada);
	// y lo mostramos
	puts("-- Padre: Resultado obtenido --\n");
	printf("\n\nresultado = <%s>\n", resultado);
	fclose(entrada);
}

void	proceso_hijo(void)
{
	FILE	*entrada;
	FILE	*salida;
	int		n;
	puts("-- Hijo: Empiezo --\n");

	//Cerramos los descriptores de archivo no usados
	close(padre_hijo[1]);
	close(hijo_padre[0]);

	//identificamos los descriptores que usará el padre
	printf("-- Hijo: Descriptores (%d, %d) --\n",
		hijo_padre[1], padre_hijo[0]);
	//Abrimos la tubería para leer del padre
	entrada = fdopen(padre_hijo[0], "r");
	if (!entrada)
	{
		puts("-- Hijo: Fallo en la apertura --\n");
		return ;
	}
	puts("-- Hijo: Tuberias preparadas --\n");
	// Leemos el dato
	if(!fscanf(entrada, " %d", &n))
	{
		puts("-- Hijo: Fallo al leer el dato --\n");
		return ;
	}
	// y cerramos 
	fclose(entrada);

	puts("-- Hijo: Leido el dato --\n");

	//Abrimos la tuberia para devolver el dato
	salida = fdopen(hijo_padre[1], "w");
	//enviamos el resultado al padre
	fprintf(salida, "- %d - ", n * n);
	puts("-- Hijo: Resultado Devuelto --\n");

	fclose(salida);
}

int	main(void)
{
	pid_t PID;

	//creamos las dos tuberias
	if (pipe(padre_hijo) || pipe(hijo_padre))
		puts("Fallo al crear la tuberia\n");
	else
	{
		PID = fork();
		if (PID)
			proceso_padre();
		else
			proceso_hijo();
	}
	return (0);
}
