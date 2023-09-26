/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/26 15:14:58 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*static void	ft_leaks(void)
{
	system("leaks -q minishell");
}*/

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	minishell;

	minishell.envp = envp;
	minishell.envlist = env_list(&minishell);
	minishell.export = env_list(&minishell);
	rl_catch_signals = 0;
//	atexit(ft_leaks);
	while (1)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
		input = readline("minishell$ ");
		if (!input)
		{
			free(input);
			ft_exit();
			return (0);
		}
		add_history(input);
		if (ft_strncmp(ft_strtrim(input, " "), "exit", 3) == 0)
		{
			free(input);
			ft_exit();
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
	return (minishell.exit_status);
}
/*
int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argc;
	(void)argv;
}
*/
