/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2024/01/09 16:42:26 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "color.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

# define READ_END 0
# define WRITE_END 1

typedef struct cmdlist
{
	char			**cmd;
	char			*path;
	char			*fd_in;
	char			*fd_out;
	int				i_fd_in;
	int				i_fd_out;
	struct cmdlist	*next;
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
	char			*line;
	char			**envp;
	char			**input;
	pid_t			child_pid;
	unsigned char	exit_status;
	int				exit;
}	t_minishell;

// Duplicación del string
char		**ft_strddup(char **envp);
void		free_str(char **str, int i);

// dividir la cadena de entrada en pequeños trozos o tokens
//para manejar mejor las tuberías, redirecciones y expansiones.
char		**ft_splitms(char const *str, char c, int word, int i);
int			ft_strcontpipex(char const *s, char c);
int			ft_strcontcmd(char const *s, char c);

//expandir las variables de entorno y las variables de shell
void		ft_expander(t_minishell *ms);
void		ft_expander_directory(t_minishell *ms);

//eliminar las comillas de la cadena de entrada (comprobar que estan pares)
void		ft_quotestrim(t_minishell *ms);

//almacenar la cadena tokenizada y guardarla de forma útil para 
//que el ejecutor pueda utilizarla posteriormente.
void		ft_parser(t_minishell *minishell);
t_cmdlist	*ft_cmdlstlast(t_cmdlist *lst);
void		ft_cmdlstadd_back(t_cmdlist **cmdlist, t_cmdlist *new);
t_cmdlist	*ft_cmdlstnew(void *content);
char		**get_paths(char **envp);
char		*ft_join(char *path, char *cmd);
char		*ft_strjoinder(char const *s1, char const *s2);
char		*ft_strjoinizq(char const *s1, char const *s2);
void		ft_free_cmdlist(t_cmdlist *cmdlist);
void		ft_lexer(t_minishell *minishell);

// Manejo y creación de la lista de variables de entorno
t_envlist	*env_list(char	**envp);
t_envlist	*lstnew_env(char *env);
void		lstadd_back_env(t_envlist **envlst, t_envlist *new);
t_envlist	*split_n_fill_env(t_envlist	*new_env, char *env);
void		sort_envlst(t_envlist **lst);
void		free_envlst(t_envlist *envlst);
void		delete_env(t_envlist **lst);
t_envlist	*check_env(char *env, t_envlist *explist);

// ejecutar los comandos
void		exec2(t_minishell *ms);

// Manejo de señales
void		ft_handler(int signum);

// Builtins
int			ft_pwd(void);
void		ft_env(t_minishell *ms);
void		ft_exit(t_minishell *ms, char **nb);
void		ft_export(t_minishell *ms, char **str);
void		ft_unset(t_minishell *ms, char **str);
void		ft_echo(char **str);
void		ft_cd(t_minishell *ms, char *str);
int			ft_bt_select(t_cmdlist *tmp, t_minishell *ms);
// Pruebas
void		testing(t_minishell *ms);

#endif