/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:14:52 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/17 21:57:55 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_export_check(char **str, t_minishell *ms, int i, int j);
static void	ft_export_add(char *str, t_minishell *ms, int diff);

int	valid_export_name(char *str)
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

void	ft_export(char **str, t_minishell *ms)
{
	int			i;
	int			j;
	t_envlist	*tmp;

	tmp = ms->explist;
	i = 0;
	j = 0;
	if (!str[0])
	{
		ft_envlst_short(&ms->explist);
		while (tmp)
		{
			printf("declare -x %s", tmp->env);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
			tmp = tmp->next;
		}
	}
	else
		ft_export_check(str, ms, i, j);
}

static void	ft_export_check(char **str, t_minishell *ms, int i, int j)
{
	t_envlist	*tmp;
	char		*var;

	while (str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != '=')
			j++;
		var = ft_calloc(sizeof(char), j + 2);
		ft_strlcpy(var, str[i], j + 1);
		tmp = ft_getenv(var, ms->explist);
		if (!tmp && valid_export_name(str[i]))
			ft_export_add(str[i], ms, str[i][j] - '=');
		else if (valid_export_name(str[i]))
		{
			free(tmp->value);
			tmp->value = ft_strdup(&str[i][j + 1]);
			ft_export_to_env(str[i], ms->envlist);
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n", str[i]);
		free(var);
		i++;
	}
}

static void	ft_export_add(char *str, t_minishell *ms, int diff)
{
	if (str[0] == '\0')
		return ;
	if (!ms->explist && !ms->envlist)
	{
		ms->explist = ft_envlstnew(str);
		if (!diff)
			ms->envlist = ft_envlstnew(str);
	}
	else
	{
		ft_envlstadd_back(&ms->explist, ft_envlstnew(str));
		if (!diff)
			ft_envlstadd_back(&ms->envlist, ft_envlstnew(str));
	}
}

void	ft_export_to_env(char *str, t_envlist *envlst)
{
	t_envlist	*tmp;
	int			i;

	i = 0;
	tmp = envlst;
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
			tmp = ft_envlst_fill(tmp, str);
			return ;
		}
		tmp = tmp->next;
	}
	ft_envlstadd_back(&envlst, ft_envlstnew(str));
}
