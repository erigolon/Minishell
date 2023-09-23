/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:25:13 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/15 15:48:15 by vicrodri         ###   ########.fr       */
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

void	ft_paths(t_minishell *minishell)
{
	int		i;

	i = 0;
	while (minishell->envp[i])
	{
		if (ft_strncmp(minishell->envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	minishell->paths = ft_calloc(ft_strlen(minishell->envp[i] + 5),
			sizeof(char));
	minishell->paths = ft_split(minishell->envp[i] + 5, ':');
}

void	ft_getcmd(t_minishell *minishell)
{
	int		i;

	i = 0;
	while (minishell->paths[i])
	{
		if (ft_strncmp(minishell->input[0], "/", 1) == 0)
			minishell->path = ft_strdup(minishell->input[0]);
		else
		{
			minishell->path = ft_strjoin(minishell->paths[i], "/");
			minishell->path = ft_strjoin(minishell->path, minishell->input[0]);
		}
		if (access(minishell->path, F_OK) == 0)
		{
			execve(minishell->path, minishell->input, minishell->envp);
			break ;
		}
		i++;
	}
	ft_printf("minishell: command not found: %s\n", minishell->input[0]);
}