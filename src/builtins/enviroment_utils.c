/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:14:35 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/17 21:55:52 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	str[0] = ft_strjoin_va("SHLVL=%i", lvl);
	ft_export(str, ms);
	free (str[0]);
	if (!ms->envlist)
	{
		str[0] = "OLDPWD\0";
		str[2] = getcwd(str[2], 0);
		str[1] = ft_strjoin_va("%s=%s", "PWD", str[2]);
		free(str[2]);
		str[2] = NULL;
		ft_export(str, ms);
		free(str[1]);
	}
	free(str);
}