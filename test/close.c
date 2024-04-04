/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:luicasad<luicasad@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:42:47 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/29 12:58:29 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int	main(void)
{
	int			fd;
	int			r;
	struct stat	sfd;

	fd = open("text.txt", O_RDONLY);
	printf("text.txt opened as [%d]  ", fd);
	fstat(fd, &sfd);
	printf("has [%lu] hard links\n", sfd.st_nlink);
	r = close(fd);
	fstat(fd, &sfd);
	printf("text.txt closed as [%d]  ", fd);
	printf("has [%lu] hard links\n", sfd.st_nlink);
	printf("text.txt closed with result [%d]\n", r);
	r = close(fd);
	fstat(fd, &sfd);
	printf("text.txt closed as [%d]  ", fd);
	printf("has [%lu] hard links\n", sfd.st_nlink);
	printf("text.txt closed with result [%d]\n", r);
	return (0);
}
