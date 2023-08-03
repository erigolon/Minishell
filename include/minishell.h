/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2023/08/03 18:26:28 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
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

#endif