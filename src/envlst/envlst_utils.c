/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:43:04 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/22 17:02:17 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envlist	*env_list(char **envp)
{
	t_envlist	*lst;
	int			i;

	i = 0;
	lst = NULL;
	if (!*envp)
		return (NULL);
	while (envp[i])
	{
		if (i == 0)
			lst = ft_envlstnew(envp[i]);
		else
			ft_envlstadd_back(&lst, ft_envlstnew(envp[i]));
		i++;
	}
	return (lst);
}

void	ft_envlst_short(t_envlist **lst)
{
	int			diff;
	char		*change;
	t_envlist	*tmp;

	tmp = *lst;
	if (!*lst)
		return ;
	while (tmp->next)
	{
		diff = ft_strncmp(tmp->env, tmp->next->env, 100);
		if (diff > 0)
		{
			change = tmp->env;
			tmp->env = tmp->next->env;
			tmp->next->env = change;
			change = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = change;
			tmp = *lst;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_envlst_to_env(t_minishell *ms)
{
	t_envlist	*tmp;
	int			i;
	char		**new;

	i = 0;
	tmp = ms->envlist;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tmp = ms->envlist;
	new = ft_calloc(sizeof(char *), i + 1);
	if (!new)
		return ;
	i = 0;
	while (tmp)
	{
		new[i] = ft_strjoin_va("%s=%s", tmp->env, tmp->value);
		i++;
		tmp = tmp->next;
	}
	ms->envp = new;
}

void	ft_envlst_del(t_envlist **lst)
{
	if (!*lst)
		return ;
	if ((*lst)->next && (*lst)->prev)
	{
		(*lst)->prev->next = (*lst)->next;
		(*lst)->next->prev = (*lst)->prev;
	}
	else if ((*lst)->next)
		(*lst)->next->prev = NULL;
	else if ((*lst)->prev)
		(*lst)->prev->next = NULL;
	(*lst)->prev = NULL;
	(*lst)->next = NULL;
	ft_free_envlst(*lst);
}
