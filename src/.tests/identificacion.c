/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identificacion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:12:53 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/14 19:57:31 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

	//si pid_son != 0 soy el padre y me espero para que se vista mi hijo.
	// ademas mi espera ayuda a que el hijo no piesne que está huerfano
	// al no encontrarme cuando se haya vestido.
//	if (pid_son)
//		sleep(0);
	// el pid obtenido del forl sera 0 para el hijo y algo para el padre.
	printf("PID obtenido de fork(): %d\n", pid_son);

	// mostramos el pid del proceso en ejecucion sea el padre o el hijo
	printf("PID de este proceso: %d\n", getpid());

	// mostramos el pid del padre de este proceso
	printf("PID de mi padres es: %d\n", getppid());

	return (0);
}

/*

== primero vemos los mensajes del hijo ya que el padre duerme 3 segundos
PID obtenido de fork(): 0
PID de este proceso: 12656
PID de mi padres es: 12655
PID obtenido de fork(): 12656
PID de este proceso: 12655
PID de mi padres es: 6694
== luego vemos los mensajes del padre.

El hijo es el 56 y dice que su padre es el 55.
El hijo no obtiene nada en el fork por que no lo ejecuta.

El padre dice que él es el 55 y que  ha creado un hijo 56.
Ademas el padre informa que el abuelo es el 6694.


== si quitamos el sleep al padre sus mensajes salen primero
PID obtenido de fork(): 12748
PID de este proceso: 12747
PID de mi padres es: 6694
PID obtenido de fork(): 0
PID de este proceso: 12748
PID de mi padres es: 3054

El padre es el 47, crea al hijo 48 y el abuelo es 6694

El hijo no tiene fork. el hijo se identifica como 48.
El hijo no puede identificar al padre.

*/
