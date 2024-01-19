/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:43:09 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/17 22:45:31 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

t_envlist	*ft_envlstnew(char *str)
{
	t_envlist	*envlst;

	envlst = (t_envlist *) ft_calloc(1, sizeof(t_envlist));
	if (!envlst)
		return (NULL);
	envlst->env = NULL;
	envlst->value = NULL;
	envlst->next = NULL;
	envlst->prev = NULL;
	ft_envlst_fill(envlst, str);
	return (envlst);
}

void	ft_envlstadd_back(t_envlist **envlst, t_envlist *add)
{
	t_envlist	*last;

	if (!envlst || !add)
		return ;
	if (!envlst)
	{
		*envlst = add;
		return ;
	}
	last = ft_envlstlast(*envlst);
	last->next = add;
	add->prev = last;
}

t_envlist	*ft_envlstlast(t_envlist *envlst)
{
	t_envlist	*last;

	last = envlst;
	if (envlst)
	{
		while (last->next)
			last = last->next;
	}
	return (last);
}

void	ft_free_envlst(t_envlist *envlst)
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

t_envlist	*ft_envlst_fill(t_envlist *envlst, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (envlst->env)
		free(envlst->env);
	envlst->env = ft_calloc(sizeof(char), i + 2);
	ft_strlcpy(envlst->env, str, i + 1);
	if (envlst->value)
		free(envlst->value);
	if (str[i] == '=')
		envlst->value = ft_strdup(&str[i + 1]);
	else
		envlst->value = NULL;
	return (envlst);
}
