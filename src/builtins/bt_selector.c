/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_selector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:47:00 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/18 15:22:01 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_bt_select(t_cmdlist *tmp, t_minishell *ms)
{
	if (!ft_strncmp(tmp->cmd[0], "cd", 3))
		return (ft_cd(ms, tmp->cmd[1]), 1);
	else if (!ft_strncmp(tmp->cmd[0], "echo", 5))
		return (ft_echo(&tmp->cmd[1]), 1);
	else if (!ft_strncmp(tmp->cmd[0], "env", 4))
		return (ft_env(ms), 1);
	else if (!ft_strncmp(tmp->cmd[0], "exit", 5))
		return (ft_exit(ms, &tmp->cmd[1]), 1);
	else if (!ft_strncmp(tmp->cmd[0], "export", 7))
		return (ft_export(ms, &tmp->cmd[1]), 1);
	else if (!ft_strncmp(tmp->cmd[0], "pwd", 4))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(tmp->cmd[0], "unset", 6))
		return (ft_unset(ms, &tmp->cmd[1]), 1);
	return (0);
}
/*
void	testing(t_minishell *ms)
{
	t_cmdlist	tmp;

	tmp.cmd = (char **)malloc(3 * sizeof(char *));
	if (tmp.cmd)
	{
		tmp.cmd[0] = ft_strdup("cd");
		tmp.cmd[1] = ft_strdup("/Users/erigolon/cursus");
		tmp.cmd[2] = NULL;
	}
	ft_bt_select(&tmp, ms);
	free(tmp.cmd[0]);
	free(tmp.cmd[1]);
	free(tmp.cmd[2]);
	free(tmp.cmd);
	ft_env(ms);
}
*/
