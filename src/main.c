/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2024/01/16 18:39:51 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void	ft_leaks(void)
// {
// 	system("leaks -q minishell");
// }

void	free_all(t_minishell *ms)
{
	free_str(ms->envp, 0);
	free_envlst(ms->envlist);
	free_envlst(ms->explist);
	free (ms);
}

void	free_loop(t_minishell *ms, char *prompt)
{
	if (!prompt || ms->input == NULL)
		return ;
	if (prompt)
		free(prompt);
	if (ms->input)
		free_str(ms->input, 0);
	if (ms->cmds)
		ft_free_cmdlist(ms->cmds);
}

t_minishell	*init_ms(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	int			i;

	(void)argc;
	(void)argv;
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

	// atexit(ft_leaks);/* Borrar esto en un futuro */
	rl_catch_signals = 0;
	ms = init_ms(argc, argv, envp);
	while (ms->exit)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
		prompt = readline(READLINE_MSG);
		if (!prompt)
		{
			ft_exit(ms, NULL);
			break ;
		}
		lex_parser(ms, prompt);
		if (prompt != NULL & ft_strlen(prompt) != 0)
			exec2(ms);
		if (!(!prompt || !*prompt))
			add_history(prompt);
		free_loop(ms, prompt);
	}
	free_all(ms);
	return (ms->exit_status);
}
