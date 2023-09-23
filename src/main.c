/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/18 11:51:50 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	ft_free_minishell(t_minishell *minishell)
{
	free(minishell->path);
	free(minishell->input);
	free_arrays(minishell->paths);
	free_arrays(minishell->input);
	free_arrays(minishell->envp);
}


int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	minishell;
	t_lexer		*lex;

	(void)argc;
	(void)argv;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell.envp = envp;
	minishell.i = 0;
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
			lex = ft_tokenizer(input, &minishell);
			// minishell.input = ft_splitpipex(input, ' ');
			// ft_paths(&minishell);
			// minishell.child_pid = fork();
			// if (minishell.child_pid == 0)
			// {
			// 	ft_getcmd(&minishell);
			// 	exit(0);
			// }
			// else
			// {
			// 	wait(NULL);
			// }
		
		}
	}	ft_free_minishell(&minishell);
	return (0);
}
