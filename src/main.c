/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2024/01/30 12:11:53 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	*g_ms;

// static void	ft_leaks(void)
// {
// 	system("leaks -q minishell");
// }

void	free_all(t_minishell *ms)
{
	free(ms->line);
	free_str(ms->envp, 0);
	free_envlst(ms->envlist);
	free_envlst(ms->explist);
	free(ms);
}

void	free_loop(t_minishell *g_ms, char *prompt, t_lexer *lex)
{
	free(prompt);
	free(g_ms->line);
	free_lexer(lex);
	if (g_ms->cmds)
		ft_free_cmdlst(g_ms);
}

t_minishell	*init_ms(int argc, char **argv, char **envp)
{
	t_minishell	*ms;

	(void)argc;
	(void)argv;
	ms = ft_calloc(1, sizeof(t_minishell));
	ms->envp = ft_strddup(envp);
	ms->envlist = env_list(envp);
	ms->explist = env_list(envp);
	ms->exit = 1;
	ms->exit_status = 0;
	ms->cmds = 0;
	return (ms);
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer		*lexer;
	char		*prompt;

	// atexit(ft_leaks);/* Borrar esto en un futuro */
	rl_catch_signals = 0;
	g_ms = init_ms(argc, argv, envp);
	while (g_ms->exit)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
		prompt = readline(READLINE_MSG);
		if (!prompt)
		{
			ft_exit(g_ms, NULL);
			break ;
		}
		lexer = lex_parser(g_ms, prompt);
		tokens_to_commands(g_ms, lexer);
		if (lexer && !lexer->error)
			exec(g_ms);
		if (!(!prompt || !*prompt))
			add_history(prompt);
		free_loop(g_ms, prompt, lexer);
	}
	free_all(g_ms);
	return (g_ms->exit_status);
}
