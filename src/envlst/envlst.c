/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:44:29 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/01 18:25:28 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envlist	*lstlast_env(t_envlist *lst)
{
	if (!lst)
		return (0);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_env(t_envlist **envlst, t_envlist *new)
{
	t_envlist	*back;

	if (envlst && new)
	{
		if (!*envlst)
			*envlst = new;
		else
		{
			back = lstlast_env(*envlst);
			back->next = new;
		}
	}
}

t_envlist	*lstnew_env(char *env)
{
	t_envlist	*new_env;

	new_env = (t_envlist *)ft_calloc(1, sizeof(t_envlist));
	if (!new_env)
		return (NULL);
	new_env->env = NULL;
	new_env->value = NULL;
	new_env->next = NULL;
	new_env->prev = NULL;
	split_n_fill_env(new_env, env);
	return (new_env);
}

t_envlist	*env_list(char	**envp)
{
	t_envlist	*lst;
	int			i;

	i = 0;
	while (envp[i])
	{
		if (i == 0)
			lst = lstnew_env(envp[i]);
		else
			lstadd_back_env(&lst, lstnew_env(envp[i]));
		i++;
	}
	return (lst);
}

void	free_envlst(t_envlist *envlst)
{
	t_envlist	*temp;

	if (!envlst)
		return ;
	while (envlst)
	{
		temp = envlst->next;
		free(envlst->env);
		if (envlst->value)
			free(envlst->value);
		free(envlst);
		envlst = temp;
	}
}