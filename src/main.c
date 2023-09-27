/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/27 12:50:52 by erigolon         ###   ########.fr       */
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
	minishell.explist = env_list(&minishell);
	rl_catch_signals = 0;
//	atexit(ft_leaks);
	minishell.exit = 1;
	while (minishell.exit)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
		input = readline(READLINE_MSG);
		if (!input)
		{
			ft_exit(&minishell);
			return (0);
		}
		add_history(input);
		if (ft_strncmp(ft_strtrim(input, " "), "exit", 3) == 0)
			ft_exit(&minishell);
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
void	init_ms(t_minishell *ms, char **envp)
{
	ms->envp = envp;
	ms->envlist = env_list(ms);
	ms->explist = env_list(ms);
	ms->exit = 1;
	ms->exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*prompt;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	init_ms(&ms, envp);
	while (ms.exit)
	{
		signal(SIGINT, ft_handler);
		prompt = readline(READLINE_MSG);
		if (!prompt)
			ft_exit(&ms);
	}
	return (ms.exit_status);
}


*/