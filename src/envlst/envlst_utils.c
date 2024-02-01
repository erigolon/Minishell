/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 22:43:04 by erigolon          #+#    #+#             */
/*   Updated: 2024/02/01 10:54:20 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_env(t_envlist **lst)
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
	free_envlst(*lst);
}

void	sort_envlst(t_envlist **lst)
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

void	envlst_to_env(t_minishell *ms)
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
		new[i] = ft_strjoin(tmp->env, "=");
		new[i] = ft_strjoin(new[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	ms->envp = new;
}

t_envlist	*check_env(char *env, t_envlist *explist)
{
	t_envlist	*tmp;

	if (!explist)
		return (NULL);
	tmp = explist;
	while (tmp)
	{
		if (!ft_strncmp(env, tmp->env, 100))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		return (tmp);
	return (NULL);
}

t_envlist	*split_n_fill_env(t_envlist *envlst, char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (envlst->env)
		free(envlst->env);
	envlst->env = ft_calloc(sizeof(char), i + 2);
	ft_strlcpy(envlst->env, env, i + 1);
	if (envlst->value)
		free(envlst->value);
	if (env[i] == '=')
		envlst->value = ft_strdup(&env[i + 1]);
	else
		envlst->value = NULL;
	return (envlst);
}
