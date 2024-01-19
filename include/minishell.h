/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2024/01/19 16:44:56 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include "parser.h"
# include "color.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>


# define READ_END 0
# define WRITE_END 1

typedef struct s_lexer	t_lexer;

typedef struct cmdlist
{
	char			**cmd;
	char			*path;
	char			*fd_in;
	char			*fd_out;
	int				i_fd_in;
	int				i_fd_out;
	int				append;
	struct cmdlist	*next;
	struct cmdlist	*prev;
}	t_cmdlist;

typedef struct envlist
{
	char			*env;
	char			*value;
	struct envlist	*next;
	struct envlist	*prev;

}	t_envlist;

typedef struct minishell
{
	struct cmdlist	*cmds;
	struct envlist	*envlist;
	struct envlist	*explist;
	int				num_com;
	int				exe;
	char			*line;
	char			**envp;
	char			**path;
	int				*pipe;
	pid_t			child_pid;
	unsigned char	exit_status;
	int				exit;
	t_lexer			*lexer;
}	t_minishell;


void	ft_handler(int signum);
void	free_str(char **str, int i);
void	free_envlst(t_envlist *envlst);
char		**ft_strddup(char **envp);
t_envlist	*env_list(char	**envp);
void		ft_exit(t_minishell *ms, char **nb);
void		ft_exit_ms(t_minishell *ms, char **num);
char	*ft_strjoin_va(char const *s, ...);
char	*ft_chrjoin(char *s1, char c);
char	*ft_ftoa(double d);
double	ft_power_double(double n, int pov);
int	ft_issign(char c);
t_envlist	*split_n_fill_env(t_envlist	*new_env, char *env);
void	free_all(t_minishell *ms);



t_lexer		*lex_parser(t_minishell *ms, char *prompt);

/*	cmdlst functions								*/
/*	create a new cmd list							*/
t_cmdlist	*ft_cmdlstnew(void);
/*	add a new nodo at the end of tje list			*/
void		ft_cmdlstadd_back(t_cmdlist **cmdlst, t_cmdlist *add);
/*	return a pointer to the last nodo of the list	*/
t_cmdlist	*ft_cmdlstlast(t_cmdlist *cmdlst);
/*	free the list									*/
void		ft_free_cmdlst(t_minishell	*ms);

/*		envlst functions							*/
t_envlist	*ft_envlstnew(char *str);
void		ft_envlstadd_back(t_envlist **envlst, t_envlist *add);
t_envlist	*ft_envlstlast(t_envlist *envlst);
void		ft_free_envlst(t_envlist *envlst);
t_envlist	*ft_envlst_fill(t_envlist *envlst, char *str);
/*		envlst utils								*/
t_envlist	*ft_copy_env(char **env);
void		ft_envlst_short(t_envlist **lst);
void		ft_envlst_to_env(t_minishell *ms);
void		ft_envlst_del(t_envlist **lst);

/*		free all at exit			*/
void		ft_free(t_minishell *ms);

/*		exit builtin				*/
/*		it change exit to 0			*/
void		ft_exit_minishell(t_minishell *ms, char **num);
int			ft_check_exit(t_minishell *ms, char *str);
__int128	ft_ato_int128(char *str);
void		ft_pwd(t_minishell *ms);
void		ft_cd(char *str, t_minishell *ms);
void		ft_echo(char **str);
/*		enviroment builtin functions						*/
void		ft_export(char **str, t_minishell *ms);
void		ft_env(t_minishell *ms);
void		ft_unset(char **str, t_minishell *ms);
void		ft_export_to_env(char *str, t_envlist *envlst);

/*
 * 		check if a variable is in the env.
 * 		with c=E is for export use, it return 0 if there is no '='
 * 		if it exist it returns the position in env[ ]
 * 		else it returns  0;						*/
int			ft_check_env(char *str, t_minishell *ms, char c);
/*		builtin utils				*/
int			ft_is_builtin(t_minishell *ms, t_cmdlist *tmp);
void		ft_accept_redirections(t_minishell *ms, t_cmdlist *tmp);
/*		enviroment utils				*/
void		ft_free_array(char **str, int i);
/*
 * 		do a copy of the array with extra space
 * 		if add is 0 it only do a copy.		*/
char		**ft_copy_array(char **src, int add);
/*
		delete 'del' items from an array.
		if del is < 1 don't do anything.		*/
void		ft_del_items_array(char **str, int del);
/*
		duplicates functionality of getenv()
		but works with the env of minishell.
		it returns a ponter to the envlst if exist
		else return NULL			*/
t_envlist	*ft_getenv(char *str, t_envlist *lst);
void		ft_shlvl_update(t_minishell *ms);
/*		redirections				*/
void		ft_exec(t_minishell *ms);
/*		redirections utils			*/
void		ft_dup(int in, int out);
void		ft_close_pipe(t_minishell *ms);
void		ft_get_path(t_minishell *ms, t_cmdlist *tmp);
void		ft_free_fork(t_minishell *ms);
/*		pruebas, para borar			*/
void		ft_pruebas(char *str, t_minishell *ms);
void		ft_prueba_wildcard(char **str);
/*		HERE_DOC					*/
/*
 * 		use readline and ft_putstr_fd 
 * 		to keep in a fd until find limiter.
 * 		return the fd to use for the next command
 * 		*/
int			ft_here_doc(char *limiter);
/*		WILDCARD					*/
/*
		return a char** with the result of use ls */
char		**ft_wildcard(char **ls);
/*
		ERRORS MSG					*/
void		ft_error_exe(char **arg, char *msg, t_minishell *ms);
void		ft_error_file(char *file, t_minishell *ms);

void		ft_prompt(t_minishell *ms);

/* signals */
void		ft_sigint(int sig);
void		ft_sigint_proc(int sig);
void		ft_signheredoc(int sig);
#endif
