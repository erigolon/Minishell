/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/17 21:32:12 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

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
	t_cmdlist		*cmds;
	struct envlist	*envlist;
	struct envlist	*export;
	char			*line;
	char			**input;
	char			**envp;
	pid_t			child_pid;
}	t_minishell;


void		ft_handler(int signum);
void		ft_handler_quit(int signum);

// dividir la cadena de entrada en pequeños trozos o tokens
//para manejar mejor las tuberías, redirecciones y expansiones.
char		**ft_splitms(char const *str, char c);
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




#endif