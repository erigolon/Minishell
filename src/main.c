/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/08/03 18:26:08 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	minishell;

	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);
		if (ft_strncmp(ft_strtrim(input, " "), "exit", 4) == 0)
		{
			free(input);
			ft_printf("exit\n");
			return (0);
		}
		else
		{
			minishell.input = ft_splitpipex(input, ' ');
			ft_paths(envp, &minishell);
			minishell.child_pid = fork();
			if (minishell.child_pid == 0)
			{
				ft_getcmd(&minishell, envp);
				exit(0);
			}
			else
				wait(NULL);
			free(input);
			free_arrays(minishell.input);
			free_arrays(minishell.paths);
		}
	}
	return (0);
}
