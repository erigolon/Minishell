/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/12 14:16:17 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	ft_free_minishell(t_minishell *minishell)
{
	free(minishell->input);
	free(minishell->envp);
}


int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	ms;

	(void)argc;
	(void)argv;
	// atexit(ft_leaks);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	ms.envp = envp;
	
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			free(input);
			printf("exit\n");
			return (0);
		}
		add_history(input);
		if (ft_strncmp(ft_strtrim(input, " "), "exit", 4) == 0)
		{
			free(input);
			ft_printf("exit\n");
			return (0);
		}
		else
		{
			ms.line = ft_strdup(input);
			// ft_expander(&ms);
			printf("after expander: %s\n", ms.line);
			ms.input = ft_splitms(ms.line, ' ');
			int i = 0;
			while (ms.input[i])
			{
				printf("%s\n", ms.input[i]);
				i++;
			}
			// ft_lexer(input, &ms);
			free(input);
			free(ms.line);
			
		}
	}	ft_free_minishell(&ms);
	return (0);
}
