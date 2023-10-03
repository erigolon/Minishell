/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/03 15:54:43 by erigolon         ###   ########.fr       */
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
	struct envlist	*explist;
	char			**envp;
	char			**input;
	pid_t			child_pid;
	unsigned char	exit_status;
	int				exit;
}	t_minishell;

// Duplicación del string
char		**ft_strddup(char **envp);
void		free_str(char **str, int i);

// Manejo y creación de la lista de variables de entorno
t_envlist	*env_list(char	**envp);
t_envlist	*split_n_fill_env(t_envlist	*new_env, char *env);
void		free_envlst(t_envlist *envlst);

// Manejo de señales
void		ft_handler(int signum);

// Builtins
int			ft_pwd(void);
void		ft_env(t_minishell *ms);

void		ft_exit(t_minishell *ms, char **nb);
void		exit_test(t_minishell *ms);

void		ft_export(t_minishell *ms);
void		ft_echo(char **str);

#endif