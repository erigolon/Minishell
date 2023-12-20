/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/12/20 11:59:50 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	free_all(t_minishell *ms)
{
	free_str(ms->envp, 0);
	free_envlst(ms->envlist);
	free_envlst(ms->explist);
	free (ms);
}

void	free_loop(t_minishell *ms, char *prompt)
{
	free(prompt);
//	free_str(ms->input, 0);
	ft_free_cmdlist(ms->cmds);
}

t_minishell	*init_ms(char **envp)
{
	t_minishell	*ms;
	int			i;

	i = 0;
	ms = ft_calloc(1, sizeof(t_minishell));
	ms->envp = ft_strddup(envp);
	ms->envlist = env_list(envp);
	ms->explist = env_list(envp);
	ms->exit = 1;
	ms->exit_status = 0;
	ms->cmds = 0;
	/* Por ahora no inicializo nada más en el struct */
	return (ms);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	char		*prompt;

	(void)argc;
	(void)argv;
	// atexit(ft_leaks);/* Borrar esto en un futuro */
	rl_catch_signals = 0;
	ms = init_ms(envp);
	while (ms->exit)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
		prompt = readline(READLINE_MSG);
		printf("prompt: %s\n", prompt); 							// **QUITAR**
		if (!prompt)
			ft_exit(ms, NULL);
		else
		{
			ms->input = ft_splitms(prompt, ' ');
			ft_expander(ms);
			ft_expander_directory(ms);
			ft_quotestrim(ms);
			int i = 0;
			while (ms->input[i])
			{
				printf("%s\n", ms->input[i]);
				// printf("%zu\n", ft_strlen(ms->input[i]));
				i++;
			}
			ft_parser(ms);
			// ft_lexer(ms);
			// pipex(ms);	
			printf("prompt: %s\n", prompt);
			if (!(!prompt || !*prompt))
				add_history(prompt);
			free_loop(ms, prompt);
			printf("prompt: %s\n", prompt);
		}
	}
	printf("exit_status: %d\n", ms->exit_status);
	free_all(ms);
	return (ms->exit_status);
}
