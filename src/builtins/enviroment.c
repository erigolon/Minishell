/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:14:41 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/17 22:39:34 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_error_unset(char *str, int *err);

void	ft_unset(char **str, t_minishell *ms)
{
	t_envlist	*tmp;
	int			i;
	int			err;

	i = 0;
	err = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (ft_strchr(str[i], '='))
			ft_error_unset(str[i], &err);
		else
		{
			tmp = ft_getenv(str[i], ms->explist);
			ft_envlst_del(&tmp);
			tmp = ft_getenv(str[i], ms->envlist);
			ft_envlst_del(&tmp);
		}
		i++;
	}
	ms->exit_status = err;
}

static void	ft_error_unset(char *str, int *err)
{
	char	*msg;

	msg = ft_strjoin("minishell: unset: \"%s\": not a valid identifier", str);
	ft_putstr_fd(msg, 2);
	*err = 1;
}

void	ft_env(t_minishell *ms)
{
	t_envlist	*tmp;

	tmp = ms->envlist;
	while (tmp)
	{
		printf("%s=%s\n", tmp->env, tmp->value);
		tmp = tmp->next;
	}
}

int	ft_check_env(char *str, t_minishell *ms, char c)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!str)
		return (-1);
	while (str[j] && str[j] != '=')
		j++;
	if (str[j] != '=' && c == 'E')
		return (-1);
	while (ms->envp[i - 1])
	{
		if (!ft_strncmp(str, ms->envp[i - 1], j) && ms->envp[i - 1][j] == '=')
			return (i);
		i++;
	}
	return (0);
}
