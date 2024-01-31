/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:13:55 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/31 17:23:32 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_no_redirections(t_minishell *ms, t_cmdlist *tmp);

int	ft_is_builtin(t_minishell *ms, t_cmdlist *tmp)
{
	if (ft_no_redirections(ms, tmp))
		return (1);
	if (!tmp || !tmp->cmd || !tmp->cmd[0])
		return (0);
	if (!ft_strncmp("cd", tmp->cmd[0], 3))
	{
		if (ms->num_com == 1)
			ft_cd(ms, tmp->cmd[1]);
		return (1);
	}
	return (0);
}

static int	ft_no_redirections(t_minishell *ms, t_cmdlist *tmp)
{
	if (!tmp || !tmp->cmd)
		return (0);
	if (!ft_strncmp("export", tmp->cmd[0], 7))
	{
		if (!tmp->cmd[1])
			return (0);
		if (ms->num_com == 1)
			ft_export(ms, &tmp->cmd[1]);
		ms->exit_status = 0;
		return (1);
	}
	else if (!ft_strncmp("unset", tmp->cmd[0], 6))
	{
		if (ms->num_com == 1)
			ft_unset(ms, &tmp->cmd[1]);
		ms->exit_status = 0;
		return (1);
	}
	else if (!ft_strncmp("exit", tmp->cmd[0], 5))
	{
		if (ms->num_com == 1)
			ft_exit(ms, &tmp->cmd[1]);
		return (1);
	}
	return (0);
}

void	ft_accept_redirections(t_minishell *ms, t_cmdlist *tmp)
{
	t_envlist	*get;

	if (!tmp || !tmp->cmd || !tmp->cmd[0])
		return ;
	if (!ft_strncmp("env", tmp->cmd[0], 4))
		ft_env(ms);
	else if (!ft_strncmp("pwd", tmp->cmd[0], 4))
		ft_pwd();
	else if (!ft_strncmp("echo", tmp->cmd[0], 5))
		ft_echo(&tmp->cmd[1]);
	else if (!ft_strncmp("getenv", tmp->cmd[0], 7))
	{
		if (!tmp->cmd[1])
			exit (0);
		get = ft_getenv(tmp->cmd[1], ms->explist);
		if (get)
			printf("%s\n", get->value);
	}
	else if (!ft_strncmp("export", tmp->cmd[0], 7))
		ft_export(ms, &tmp->cmd[1]);
	else
		return ;
	ft_free_fork(ms);
	exit (0);
}
