/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/02 12:42:34 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_leaks(void)
{
	system("leaks -q minishell");
}
/*
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
*/

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
	ms->cmdlist = 0;
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
			ft_exit(ms);
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
