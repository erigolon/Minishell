/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2024/01/18 19:26:55 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void	ft_leaks(void)
// {
// 	system("leaks -q minishell");
// }

static void	ft_clean(t_minishell *g_ms, char *prompt, t_lexer *lex);


t_minishell		*g_ms;


void	free_all(t_minishell *ms)
{
	free(ms->line);
	ft_free_array(ms->envp, 0);
	ft_free_envlst(ms->envlist);
	ft_free_envlst(ms->explist);
	free(ms);
}

void	free_loop(t_minishell *ms, char *prompt)
{
	(void)ms;
	if (prompt)
		free(prompt);
}

t_minishell	*init_ms(int argc, char **argv, char **envp)
{
	t_minishell	*ms;

	(void)argc;
	(void)argv;
	ms = ft_calloc(1, sizeof(t_minishell));
	ms->envp = ft_strddup(envp);
	ms->envlist = ft_copy_env(envp);
	ms->explist = ft_copy_env(envp);
	ms->exit = 1;
	ms->exit_status = 0;
	ms->cmds = 0;
	/* Por ahora no inicializo nada más en el struct */
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
			ft_exit_ms(g_ms, NULL);
			break ;
		}
		lexer = lex_parser(g_ms, prompt);
		tokens_to_commands(g_ms, lexer);
		if (lexer && !lexer->error)
			ft_exec(g_ms);
		if (!(!prompt || !*prompt))
			add_history(prompt);
		ft_clean(g_ms, prompt, lexer);
	}
	free_all(g_ms);
	return (g_ms->exit_status);
}
static void	ft_clean(t_minishell *g_ms, char *prompt, t_lexer *lex)
{
	free(prompt);
	free(g_ms->line);
	lexer_free(lex);
	if (g_ms->cmds)
		ft_free_cmdlst(g_ms);
}

void	ft_free(t_minishell *ms)
{
	free(ms->line);
	ft_free_array(ms->envp, 0);
	ft_free_envlst(ms->envlist);
	ft_free_envlst(ms->explist);
	free(ms);
}