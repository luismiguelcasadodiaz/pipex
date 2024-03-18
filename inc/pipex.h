/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:51:53 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/18 14:17:11 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# define PIPEX_INPUT 0
# define PIPEX_OUTPUT 1
# define READ 0
# define WRITE 1
# define KO 0
# define OK 1

/******************************************************************************/
/**
   @file pipex.h
   @struct s_pipex_args holds absolute paths to files and command used 

   @var  cmd: command name.
   @var  arg: list of argument ot pass to the command.

   @details
   A pipex argument like "ls -al" will be separated in two parts, the command
   "ls" and the flags " -al". please notice the whitspace.

   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
typedef struct s_cmd
{
	char	*cmd;
	char	*cli;
	char	**flg;
	int		is_r;
	int		is_x;
	int		fd_i;
	int		fd_o;
}	t_cmd;

/* ************************************************************************** */
/* create_cmd() initializes a t_cmd structure.                                */
/* ************************************************************************** */
t_cmd			*cmd_create(char *cmd, char **flg);
/* ************************************************************************** */
/* destroy_cmd() frees memory used by a t_cmd structure.                      */
/* ************************************************************************** */
void			cmd_destroy(t_cmd *cmd);
/******************************************************************************/
/**
   @file pipex.h
   @struct s_pipex_args holds absolute paths to files and command used 

   @var  max_cmds: number of commands in pipe, comes from argc minus 3.
   @var  num_cmds: number of commands verified wiht accesible absolute path.
   @var    infile: verified and accesible absolute path for infile.
   @var   outfile: verified and accesible absolute path for outfile.
   @var    **cmds: array of verified and accesible absolute paths to commands
   @var    all_ok: indicates if all files and commands are ok = 1.


   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
typedef struct s_pipex_args
{
	int		max_cmds;
	int		num_cmds;
	short	all_ok;
	char	*path;
	char	*pwd;
	char	*infile;
	int		free_infile;
	char	*in_arg;
	char	*outfile;
	int		free_outfile;
	char	*ou_arg;
	t_cmd	**cmds;
}	t_pipex_args;

/* ************************************************************************** */
/* create() initializes a t_pipex_args structure.                             */
/* ************************************************************************** */
t_pipex_args	create(int max_cmds);
/* ************************************************************************** */
/* destroy() frees memory used by a t_pipex_args structure.                   */
/* ************************************************************************** */
void			destroy(t_pipex_args args);
/* ************************************************************************** */
/* execute() forks and control child processes                                */
/* ************************************************************************** */
void			execute(t_pipex_args pip_arg, char **env);
void			read_or_exit(t_pipex_args args, int idx);
void			write_or_exit(t_pipex_args args, int idx);
/* ************************************************************************** */
/* set_file() assign absolute path to file in the right slot                  */
/* ************************************************************************** */
void			set_file(t_pipex_args *pip_arg, char *file, int direc);
/* ************************************************************************** */
/* show_pipex_args() prints t_pipex_args variable content                     */
/* ************************************************************************** */
void			show_pipex_args(t_pipex_args args);
#endif
