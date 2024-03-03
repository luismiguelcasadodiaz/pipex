/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:14 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/03 23:52:32 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

void	execute(t_pipex_args args, char **env)
{
	//int		i;
	pid_t	PID;
	int		resultado;

	PID = fork();
	if (PID != 0)
	{
		execve(args.cmds[0]->cmd, args.cmds[0]->flg, env); 
		wait(&resultado);
		ft_printf("El resultado del proceso padre %s ha sido %d\n", args.cmds[0]->cmd, resultado);
	}
	else
	{
		execve(args.cmds[args.max_cmds -1]->cmd, args.cmds[args.max_cmds -1]->flg, env);
		wait(&resultado);
		ft_printf("El resultado del proceso hijo %s ha sido %d\n", args.cmds[args.max_cmds - 1]->cmd, resultado);
	}
	/*ft_printf("Execute < %s %s%s\n ", args.infile, args.cmds[0]->cmd, args.cmds[0]->flg);
	execve(args.cmds[0]->cmd, args.cmds[0]->flg, env); 
	i = 1;
	while (i < (args.max_cmds -1))
	{
		ft_printf("| %s%s ", args.cmds[i]->cmd, args.cmds[i]->flg);
		execve(args.cmds[i]->cmd, args.cmds[i]->flg, env);
		i++;
	}
	ft_printf("| %s%s > %s\n", args.cmds[args.max_cmds -1]->cmd, args.cmds[args.max_cmds -1]->flg, args.outfile);
	execve(args.cmds[args.max_cmds -1]->cmd, args.cmds[args.max_cmds -1]->flg, env);
	*/
}
