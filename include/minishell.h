/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/18 12:04:02 by vicrodri         ###   ########.fr       */
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
}	t_minishell;

char	**ft_splitpipex(char const *str, char c);
void	ft_paths(t_minishell *minishell);
void	ft_getcmd(t_minishell *minishell);
void	free_arrays(char **arg);
void	ft_pipe(t_minishell *minishell);
void	ft_handler(int signum);
void	ft_handler_quit(int signum);
t_lexer *ft_tokenizer(char *input, t_minishell *minishell);

#endif