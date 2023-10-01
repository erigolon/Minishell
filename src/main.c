/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/27 21:42:32 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	ft_free_minishell(t_minishell *minishell)
{
	free(minishell->input);
}


int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell.envp = envp;
	
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
			ft_tokenizer(input, &minishell);
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
