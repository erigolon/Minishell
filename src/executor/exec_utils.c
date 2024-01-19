/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:09:33 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/19 17:10:07 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_dup(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	ft_close_pipe(t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < (ms->num_com * 2 - 1))
	{
		close(ms->pipe[i]);
		i++;
	}
}

void	ft_get_path(t_minishell *ms, t_cmdlist *tmp)
{
	int	i;

	i = 0;
	if (!access(tmp->cmd[i], F_OK))
	{
		tmp->path = tmp->cmd[i];
		return ;
	}
	if (!ms->path || tmp->cmd[0][0] == '\0')
		return ;
	while (ms->path[i])
	{
		tmp->path = ft_strjoin_va("%s/%s", ms->path[i], tmp->cmd[0]);
		if (!access(tmp->path, F_OK))
		{
			return ;
		}
		free(tmp->path);

		i++;
	}
	tmp->path = NULL;
}

void	ft_free_fork(t_minishell *ms)
{
	lexer_free(ms->lexer);
	free(ms->pipe);
	if (ms->path)
		ft_free_array(ms->path, 0);
	ft_free_cmdlst(ms);
	free_all(ms);
}
