/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:51:53 by luicasad          #+#    #+#             */
/*   Updated: 2024/03/20 11:20:01 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
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

   @var  cli: command line argument "wc" only.
   @var  cmd: command name wiht absolute path. "/usr/bin/wc"
   @var  flg: **char ready to pass it to execve "/usr/bin/wc" "-l" "NULL"
   @var  arg: list of argument ot pass to the command.
   @var	 pfd: array with 2 file descriptors to holde a pipe.

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
	int		pfd[2];
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
   @var  num_cmds: number of commands with verified  absolute path.
   @var	 exe_cmds: number of executed commands
   @var    all_ok: indicates if all files and commands are ok = 1.
   @var      path: Holds PATH enviromental var 
   @var       pwd: Holdes PWD enviromental var
   @var    in_arg: infile filename passed in CLI
   @var    infile: Path to infile.
   @var	  free_in: Flag. If 1 frees a strjoined infile (not starting by '/')
   @var    ou_arg: oitfile filename passed in CLI
   @var   outfile: path to outfile.
   @var	  free_ou: Flag. If 1 frees a strjoined outfile (not starting by '/')
   @var    **cmds: array of strucutures holding commands variables


   @author LMCD (Luis Miguel Casado Díaz)
 *****************************************************************************/
typedef struct s_pipex_args
{
	int		max_cmds;
	int		num_cmds;
	int		exe_cmds;
	short	all_ok;
	char	*path;
	char	*pwd;
	char	*in_arg;
	char	*infile;
	int		free_in;
	char	*ou_arg;
	char	*outfile;
	int		free_ou;
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
/* ************************************************************************** */
/* arg_ok() checks argument sent to pipex                                     */
/* ************************************************************************** */
void	arg_ok(int argc, char **argv, char **environ, t_pipex_args *pip_arg);
char	*arg_val_var(char *var);
char	*arg_fin_env_var(char **environ, char *var);
void	arg_is_in_file(char *arg, t_pipex_args *pip_arg);
void	arg_is_ou_file(char *arg, t_pipex_args *pip_arg);
char	*arg_fin_com(char *com, t_pipex_args *pip_arg);
void	arg_is_command(char *arg, t_pipex_args *pip_arg);
char    *arg_find_point_slash(char *com, t_pipex_args *p);
#endif
