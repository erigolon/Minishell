/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/18 15:21:50 by erigolon         ###   ########.fr       */
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
	/* Aquí liberaremos cosas que usamos en el bucle como:
	LEX
	LSTCMD
	*/
}

t_minishell	*init_ms(char **envp)
{
	t_minishell	*ms;

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
	atexit(ft_leaks);/* Borrar esto en un futuro */
	rl_catch_signals = 0;
	ms = init_ms(envp);
	while (ms->exit)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
		prompt = readline(READLINE_MSG);
		if (!prompt)
			ft_exit(ms, NULL);
		/* Hacer cositas con el prompt que nos entra: 
		LEX
		PARSEO
		EXECUTOR
		*/
		add_history(prompt); // Ahora guarda todo, pero solo de be guardar lo que funciona
		free_loop(ms, prompt); /* Liberar elementos que haya utilizado ahora */
	}
	free_all(ms);
	return (ms->exit_status);
}
