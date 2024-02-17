/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 09:56:55 by luicasad          #+#    #+#             */
/*   Updated: 2024/02/17 10:41:49 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <time.h>
#include <stdlib.h>

void	procesohijo()
{	int n;

	n = 0;
	while (n < 10)
	{
		printf(" <%d> ", n++);
		fflush(stdout);
		sleep(2);
	}
}
int	main()
{
	pid_t	pid;
	clock_t	antes;
	clock_t	ahora;
	int		wait_result;
	int		son_result;
	short	esperando;

	pid = fork();
	antes = clock();

	if (pid != -1)
		if (!pid)
			procesohijo();
		else
		{
			printf("Soy el padre %d que espera termine el hijo %d ...", getpid(), pid);
			esperando = 1;
			while (esperando)
			{
				wait_result = waitpid(pid, &son_result, WNOHANG);
				esperando = !wait_result;
				ahora = clock();
				if (((ahora - antes) / CLOCKS_PER_SEC) >= 1)
				{
					printf("%d \n", wait_result);
					fflush(stdout);
					antes = ahora;
				}
			}
			printf("\n Proceso hijo finalizado con %d \n", son_result);
			printf("\n El wait result dion %d \n", wait_result);
		}
	else
		puts("He tenido problemas con el fork\n");
	return (0);
}
