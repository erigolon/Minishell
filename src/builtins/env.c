/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:34:32 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/30 11:13:31 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_minishell *ms)
{
	t_envlist	*lst;

	lst = ms->envlist;
	while (lst)
	{
		if (lst->value)
			printf("%s=%s\n", lst->env, lst->value);
		lst = lst->next;
	}
}

t_envlist	*ft_getenv(char *str, t_envlist *lst)
{
	t_envlist	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->env, 100))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		return (tmp);
	return (NULL);
}

void	ft_shlvl_update(t_minishell *ms)
{
	t_envlist	*tmp;
	char		**str;
	int			lvl;

	tmp = ft_getenv("SHLVL", ms->explist);
	str = ft_calloc(sizeof(char *), 4);
	lvl = 1;
	if (ms->explist && tmp && tmp->value)
		lvl = ft_atoi(tmp->value) + 1;
	str[0] = ft_strjoin("SHLVL=", ft_itoa(lvl));
	ft_export(ms, str);
	free (str[0]);
	if (!ms->envlist)
	{
		str[0] = "OLDPWD\0";
		str[2] = getcwd(str[2], 0);
		str[1] = ft_strjoin("PWD=", str[2]);
		free(str[2]);
		str[2] = NULL;
		ft_export(ms, str);
		free(str[1]);
	}
	free(str);
}
