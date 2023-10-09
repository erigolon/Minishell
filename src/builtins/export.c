/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:37:50 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/09 11:39:02 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_to_list(char *str, t_minishell *ms)
{
	t_envlist	*tmp;
	int			i;

	i = 0;
	tmp = ms->envlist;
	if (!str)
		return ;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return ;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->env, i) && !tmp->env[i])
		{
			tmp = split_n_fill_env(tmp, str);
			return ;
		}
		tmp = tmp->next;
	}
	lstadd_back_env(&ms->envlist, lstnew_env(str));
}

void	add_new_env(char *str, t_minishell *ms)
{
	if (str[0] == '\0')
		return ;
	if (!ms->explist && ms->envlist)
	{
		ms->explist = lstnew_env(str);
		ms->envlist = lstnew_env(str);
	}
	else
	{
		lstadd_back_env(&ms->explist, lstnew_env(str));
		lstadd_back_env(&ms->envlist, lstnew_env(str));
	}
}

int	check_env_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_env(t_minishell *ms, char **str, int i)
{
	t_envlist	*tmp;
	char		*env;
	int			o;

	while (str[i])
	{
		o = 0;
		while (str[i][o] && str[i][o] != '=')
			o++;
		env = ft_calloc(sizeof(char), o + 2);
		ft_strlcpy(env, str[i], o + 1);
		tmp = check_env(env, ms->explist);
		if (!tmp && check_env_name(str[i]))
			add_new_env(str[i], ms);
		else if (check_env_name(str[i]))
		{
			free(tmp->value);
			tmp->value = ft_strdup(&str[i][o + 1]);
			export_to_list(str[i], ms);
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n", str[i]);
		free(env);
		i++;
	}
}

void	ft_export(t_minishell *ms, char **str)
{
	t_envlist	*lst;

	lst = ms->explist;
	if (!str[0])
	{
		sort_envlst(&ms->explist);
		while (lst)
		{
			printf("declare -x %s", lst->env);
			if (lst->value)
				printf("=\"%s\"", lst->value);
			printf("\n");
			lst = lst->next;
		}
	}
	else
		export_env(ms, str, 0);
}
