/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:25:13 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/22 12:41:11 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	free_arrays(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	ft_paths(char **envp, t_minishell *minishell)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	minishell->paths = ft_calloc(ft_strlen(envp[i] + 5), sizeof(char));
	minishell->paths = ft_split(envp[i] + 5, ':');
}

void	ft_getcmd(t_minishell *minishell, char **envp)
{
	int		i;

	i = 0;
	while (minishell->paths[i])
	{
		minishell->cmd = ft_strjoin(minishell->paths[i], "/");
		minishell->cmd = ft_strjoin(minishell->cmd, minishell->input[0]);
		if (access(minishell->cmd, F_OK) == 0)
		{
			execve(minishell->cmd, minishell->input, envp);
			break ;
		}
		i++;
	}
	ft_printf("minishell: command not found: %s\n", minishell->input[0]);
}
