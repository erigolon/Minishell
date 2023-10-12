/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/12 11:55:41 by erigolon         ###   ########.fr       */
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

typedef struct minishell
{
	char	**paths;
	char	**input;
	char	*cmd;
	int		child_pid;
}	t_minishell;

char	**ft_splitpipex(char const *str, char c);
void	ft_paths(char **envp, t_minishell *minishell);
void	ft_getcmd(t_minishell *minishell, char **envp);
void	free_arrays(char **arg);
void	ft_handler(int signum);
void	ft_handler_quit(int signum);

#endif