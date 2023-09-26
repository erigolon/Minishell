/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/26 13:03:26 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct token
{
	int				type;
	char			*str;
	int				status;
	int				escaped;
	int				join_next;
	struct token	*next;
	struct token	*prev;
}	t_token;

typedef struct lexer
{
	struct token	*token_list;
	int				n_tokens;
	int				error;
}	t_lexer;

typedef struct cmdlist
{
	char			**arg;
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
	struct cmdlist	*cmdlist;
	struct envlist	*envlist;
	struct envlist	*export;
	t_lexer			*lexer;
	char			**paths;
	char			*path;
	char			**input;
	pid_t			child_pid;
	char			**envp;
	int				fd_pipe[2];
	int				i;
	int				i_pipe;
	unsigned char	exit_status;
	int				exit;
	char			*cmd;
}	t_minishell;

char		**ft_splitpipex(char const *str, char c);
void		ft_paths(char **envp, t_minishell *minishell);
void		ft_getcmd(t_minishell *minishell, char **envp);
void		free_arrays(char **arg);

// Manejo y creación de la lista de variables de entorno
t_envlist	*env_list(t_minishell *ms);
t_envlist	*split_n_fill_env(t_envlist	*new_env, char *env);

// Manejo de señales
void		ft_handler(int signum);

// Builtins
int			ft_pwd(void);
void		ft_env(t_minishell *ms);
void		ft_exit(void);
void	ft_export(t_minishell *ms);

#endif