/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/17 21:14:27 by erigolon         ###   ########.fr       */
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
			ms.input = ft_splitms(input, ' ');
			ft_expander(&ms);
			ft_expander_directory(&ms);
			ft_quotestrim(&ms);
			int i = 0;
			while (ms.input[i])
			{
				printf("%s\n", ms.input[i]);
				printf("%zu\n", ft_strlen(ms.input[i]));
				i++;
			}
			// ft_parser(&ms);
			free(input);
			free(ms.line);
		}
	}	ft_free_minishell(&ms);
	return (0);
}
