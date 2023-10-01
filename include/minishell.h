/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/01 19:38:53 by vicrodri         ###   ########.fr       */
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
	char			**input;
	char			**envp;
	pid_t			child_pid;
}	t_minishell;

char	**ft_splitpipex(char const *str, char c);
void	ft_paths(t_minishell *minishell);
void	ft_getcmd(t_minishell minishell, char *cmdargs);
void	ft_pipe(t_minishell *minishell);
void	ft_handler(int signum);
void	ft_handler_quit(int signum);
void	ft_parser(t_minishell minishell);
void	ft_tokenizer(char *input, t_minishell *minishell);

#endif