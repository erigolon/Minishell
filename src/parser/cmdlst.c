/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:10:03 by juan-aga          #+#    #+#             */
/*   Updated: 2024/01/16 19:45:56 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmdlist	*ft_cmdlstnew(void)
{
	t_cmdlist	*cmdlist;

	cmdlist = (t_cmdlist *) ft_calloc(1, sizeof(t_cmdlist));
	if (!cmdlist)
		return (NULL);
	cmdlist->path = NULL;
	cmdlist->cmd = NULL;
	cmdlist->fd_in = NULL;
	cmdlist->fd_out = NULL;
	cmdlist->i_fd_in = 0;
	cmdlist->i_fd_out = 1;
	cmdlist->append = 0;
	cmdlist->next = NULL;
	cmdlist->prev = NULL;
	return (cmdlist);
}

void	ft_cmdlstadd_back(t_cmdlist **cmdlist, t_cmdlist *add)
{
	t_cmdlist	*last;

	if (!cmdlist || !add)
		return ;
	if (!cmdlist)
	{
		*cmdlist = add;
		return ;
	}
	last = ft_cmdlstlast(*cmdlist);
	last->next = add;
	add->prev = last;
}

t_cmdlist	*ft_cmdlstlast(t_cmdlist *cmdlist)
{
	t_cmdlist	*last;

	last = cmdlist;
	if (cmdlist)
	{
		while (last->next)
		last = last->next;
	}
	return (last);
}

void	ft_free_cmdlst(t_minishell	*ms)
{
	t_cmdlist	*tmp;
	t_cmdlist	*cmdlist;

	cmdlist = ms->cmds;
	while (cmdlist)
	{
		tmp = cmdlist->next;
		if (cmdlist->path)
			free(cmdlist->path);
		if (cmdlist->cmd)
			ft_free_array(cmdlist->cmd, 0);
		free(cmdlist);
		cmdlist = tmp;
	}
	ms->cmds = 0;
}
