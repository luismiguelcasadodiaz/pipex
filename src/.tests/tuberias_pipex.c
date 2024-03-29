/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuberias_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:25:51 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/03 10:44:31 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LENGTH 256
#define PADRE_HIJO 0
#define HIJO_PADRE 1
#define MAX_PIPES 10
#define IN 0
#define OUT 1


/* ************************************************************************** */
/*                                                                            */
/*   |------- father ------|                    |-------  son  ------|        */
/*   | __________________  |                    | _________________  |        */
/*   | |(in) f-> s  (out)| |    pipe[0]         | |(in) f-> s (out)| |        */
/*   | |_________________| |                    | |________________| |        */
/*   |  x              >   |                    |   >             x  |        */
/*   | __________________  |                    | _________________  |        */
/*   | |(in) s-> f  (out)| |    pipe[1]         | |(in) s-> f (out)| |        */
/*   | |_________________| |                    | |________________| |        */
/*   |   >             x   |                    |   x           >    |        */
/*   |_____________________|                    |____________________|        */
/*                                                                            */
/*    closes: f->s (in )                          closes: f->s (out)          */
/*    closes: s->f (out)                          closes: s->f (in )          */
/*    writes: f->s (out)                          reads : f->s (in )          */
/*    reads : s->f (in )                          writes: s->f (out)          */
/*                                                                            */
/* ************************************************************************** */

void	proceso_padre(int pipes[][2], int count)
{
	FILE	*entrada;
	FILE	*salida;
	char	resultado[MAX_LENGTH];

	puts("-- Padre: Empiezo --\n");

	//Cerramos los descriptores de archivo no usados
	close(pipes[count][IN]);
	close(pipes[count + 1][OUT]);

	//identificamos los descriptores que usará el padre
	printf("-- Padre: Descriptores (%d, %d) --\n",
		pipes[count][OUT], pipes[count + 1][IN]);

	// Abrimos la salida hacia el hijo
	salida = fdopen(pipes[count][OUT], "w");
	if (!salida)
	{
		puts("-- Padre: Fallo en la apertura --\n");
		return ;
	}

	//La tuberia está preparada
	puts("-- Padre: Tuberias preparadas -- \n"); 

	//Enviamos el dato que debe operar el hijo
	if (fputs("2", salida) == EOF)
	{
		puts("-- Padre: Fallo al escribir --\n");
		return ;
	}
	// y cerramos 
	fclose(salida);
	puts("-- Padre: Envido el dato --\n");

	// Abrimos la tubería para recoger el dato del hijo
	entrada = fdopen(pipes[count + 1][IN], "r");
	//Leemos el resultado
	fgets(resultado, MAX_LENGTH, entrada);
	// y lo mostramos
	puts("-- Padre: Resultado obtenido --\n");
			printf("\n\nresultado = <%s>\n", resultado);
	fclose(entrada);
}

void	proceso_hijo(int pipes[][2], int count)
{
	FILE	*entrada;
	FILE	*salida;
	int		n;
	puts("-- Hijo: Empiezo --\n");

	//Cerramos los descriptores de archivo no usados
	close(pipes[count - 1][OUT]);
	close(pipes[count][IN]);

	//identificamos los descriptores que usará el padre
	printf("-- Hijo: Descriptores (%d, %d) --\n",
		pipes[count - 1][IN], pipes[count][OUT]);
	//Abrimos la tubería para leer del padre
	entrada = fdopen(pipes[count - 1][IN], "r");
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
	salida = fdopen(pipes[HIJO_PADRE][OUT], "w");
	//enviamos el resultado al padre
	fprintf(salida, "- %d - ", n * n);
	puts("-- Hijo: Resultado Devuelto --\n");

	fclose(salida);
}

int	main(int argc, char **argv)
{
	int	pipes[MAX_PIPES][2];

	pid_t PID;
	int 	i;
	short	exito;
	int		num_proc;

	if (argc !=2)
	{		puts("usage is ./tuberias_pipex <num_proc>\n");
	}
	num_proc = atoi(argv[1]);
	i = -1;
	exito = 1;
	while (++i < MAX_PIPES && exito)
	{
		exito = exito && (pipe(pipes[i]) == 0);
		printf("Tuberia %d ==> (%d|%d)\n", i, pipes[i][0], pipes[i][1]);
	}
	if (!exito)
	{
		printf("Fallo al crear la ddtuberia %d\n", i);
		return (-1);
	}
	i = 0;
	while (i < (num_proc -1))
	{
		PID = fork();
		if (PID)
			proceso_padre(pipes, i);
		else
			proceso_hijo(pipes, i + 1);
		i++;
	}
	return (0);
}
