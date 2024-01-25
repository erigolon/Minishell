/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:43:09 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/25 19:31:07 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envlist	*lstlast_env(t_envlist *envlst)
{
	t_envlist	*lst;

	lst = envlst;
	if (envlst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	lstadd_back_env(t_envlist **envlst, t_envlist *new)
{
	t_envlist	*back;

	if (!envlst || !new)
		return ;
	if (!envlst)
	{
		*envlst = new;
		return ;
	}
	back = lstlast_env(*envlst);
	back->next = new;
	new->prev = back;
}

t_envlist	*lstnew_env(char *env)
{
	t_envlist	*new_env;

	new_env = (t_envlist *) ft_calloc(1, sizeof(t_envlist));
	if (!new_env)
		return (NULL);
	new_env->env = NULL;
	new_env->value = NULL;
	new_env->next = NULL;
	new_env->prev = NULL;
	ft_envlst_fill(new_env, env);
	return (new_env);
}

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
			lstadd_back_env(&lst, lstnew_env(envp[i]));
		i++;
	}
	return (lst);
}

void	free_envlst(t_envlist *envlst)
{
	t_envlist	*tmp;

	while (envlst)
	{
		tmp = envlst->next;
		free(envlst->env);
		if (envlst->value)
			free(envlst->value);
		free(envlst);
		envlst = tmp;
	}
}
