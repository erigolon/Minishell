/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2024/01/25 19:31:25 by vicrodri         ###   ########.fr       */
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
void		ft_exit(t_minishell *ms, char **nb);
char	*ft_strjoin_va(char const *s, ...);
char	*ft_chrjoin(char *s1, char c);
char	*ft_ftoa(double d);
double	ft_power_double(double n, int pov);
int	ft_issign(char c);
t_envlist	*split_n_fill_env(t_envlist	*new_env, char *env);



void		ft_exit(t_minishell *ms, char **nb);

void	free_all(t_minishell *ms);
void	free_loop(t_minishell *g_ms, char *prompt, t_lexer *lex);


// // Duplicación del string
// char		**ft_strddup(char **envp);
// void		free_str(char **str, int i);

// // dividir la cadena de entrada en pequeños trozos o tokens
// //para manejar mejor las tuberías, redirecciones y expansiones.
// char		**ft_splitms(char const *str, char c, int word, int i);
// int			ft_strcontpipex(char const *s, char c);
// int			ft_strcontcmd(char const *s, char c);

// //expandir las variables de entorno y las variables de shell
// void		ft_expander(t_minishell *ms);
// void		ft_expander_directory(t_minishell *ms);

// //eliminar las comillas de la cadena de entrada (comprobar que estan pares)
// void		ft_quotestrim(t_minishell *ms);

// //almacenar la cadena tokenizada y guardarla de forma útil para 
// //que el ejecutor pueda utilizarla posteriormente.
// void		ft_parser(t_minishell *minishell);
// t_cmdlist	*ft_cmdlstlast(t_cmdlist *lst);
// void		ft_cmdlstadd_back(t_cmdlist **cmdlist, t_cmdlist *new);
// t_cmdlist	*ft_cmdlstnew(void);
// char		**get_paths(char **envp);
// char		*ft_join(char *path, char *cmd);
// char		*ft_strjoinder(char const *s1, char const *s2);
// char		*ft_strjoinizq(char const *s1, char const *s2);
// void		ft_free_cmdlist(t_cmdlist *cmdlist);
// void		ft_lexer(t_minishell *minishell);

// // Manejo y creación de la lista de variables de entorno
// t_envlist	*env_list(char	**envp);
// t_envlist	*lstnew_env(char *env);
// void		lstadd_back_env(t_envlist **envlst, t_envlist *new);
// t_envlist	*split_n_fill_env(t_envlist	*new_env, char *env);
// void		sort_envlst(t_envlist **lst);
// void		free_envlst(t_envlist *envlst);
// void		delete_env(t_envlist **lst);
// t_envlist	*check_env(char *env, t_envlist *explist);

// // ejecutar los comandos
// void		exec2(t_minishell *ms);

// // Manejo de señales
// void		ft_handler(int signum);

// // Builtins
// int			ft_pwd(void);
// void		ft_env(t_minishell *ms);
// void		ft_exit(t_minishell *ms, char **nb);
// void		ft_export(t_minishell *ms, char **str);
// void		ft_unset(t_minishell *ms, char **str);
// void		ft_echo(char **str);
// void		ft_cd(t_minishell *ms, char *str);
// int			ft_bt_select(t_cmdlist *tmp, t_minishell *ms);
// // Pruebas
// void		testing(t_minishell *ms);

// void		lex_parser(t_minishell *ms, char *prompt);

// #endif











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
t_envlist	*lstnew_env(char *env);
void		envlstadd_back(t_envlist **envlst, t_envlist *add);
void	lstadd_back_env(t_envlist **envlst, t_envlist *new);
void		free_envlst(t_envlist *envlst);
t_envlist	*split_n_fill_env(t_envlist *envlst, char *env);
/*		envlst utils								*/
t_envlist	*env_list(char	**envp);
void	sort_envlst(t_envlist **lst);
void		ft_envlst_to_env(t_minishell *ms);
void		delete_env(t_envlist **lst);

/*		free all at exit			*/
void		ft_free(t_minishell *ms);

/*		exit builtin				*/
/*		it change exit to 0			*/
void		ft_exit_minishell(t_minishell *ms, char **num);
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
void		exec(t_minishell *ms);
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
