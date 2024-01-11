/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:26 by vicrodri          #+#    #+#             */
/*   Updated: 2024/01/11 13:23:58 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void	mini_getpid(t_minishell *ms)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		exit(1);
// 	}
// 	if (!pid)
// 	{
// 		exit(1);
// 	}
// 	waitpid(pid, NULL, 0);
// 	ms->child_pid = pid - 1;
// }

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
	free(prompt);
	free_str(ms->input, 0);
	write(1, "primero", 7); //
	if (ms->cmds)
	{
		write(1, "segundo", 7); //
		ft_free_cmdlist(ms->cmds);
	}
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
//	mini_getpid(ms);
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
		ms->input = ft_splitms(prompt, ' ', 0, 0);
		ft_expander(ms);
		ft_parser(ms);
		exec2(ms);
		if (!(!prompt || !*prompt))
			add_history(prompt);
		free_loop(ms, prompt);
	}
	printf("exit_status: %d\n", ms->exit_status);
	free_all(ms);
	return (ms->exit_status);
}
