/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redireccion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:53:32 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/14 19:03:28 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	FILE *grep;
	FILE *man;
	char c;

	// Ejecutamos el comando grep para buscar ocurrencias de la palabra Linux.
	// Redirigimos la entrada standard del proceso con w.
	// Así podemos escribir en la entrada standar del proceso grep.
	grep = popen("grep Linux", "w");

	// ejecutamos el comando man gcc.
	// Redirecionamos la salida standard del proceso con r.
	// Asi podemos ller la salida standard del proceso man
	man = popen("man gcc", "r");

	// mientras que hay caracteres en la salida standard de man
	// se los pasamos a la entrada estandar de grep
	while ((c = fgetc(man)) != EOF)
		fputc(c, grep);

	// cerramos los canales de comunicacion;
	pclose(grep);
	pclose(man);
	return (0);
}
