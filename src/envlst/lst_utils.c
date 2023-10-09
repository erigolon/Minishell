/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:26:30 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/05 11:24:30 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	sort_envlst(t_envlist **lst)
{
	t_envlist	*tmp;
	char		*swap;

	tmp = *lst;
	if (!*lst)
		return ;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->env, tmp->next->env, 100) > 0)
		{
			swap = tmp->env;
			tmp->env = tmp->next->env;
			tmp->next->env = swap;
			swap = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = swap;
			tmp = *lst;
		}
		else
			tmp = tmp->next;
	}
}

t_envlist	*split_n_fill_env(t_envlist	*new_env, char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (new_env->env)
		free(new_env->env);
	new_env->env = ft_calloc(sizeof(char), i + 2);
	ft_strlcpy(new_env->env, env, i + 1);
	if (new_env->value)
		free(new_env->value);
	if (env[i] == '=')
		new_env->value = ft_strdup(&env[i + 1]);
	else
		new_env->value = NULL;
	return (new_env);
}
