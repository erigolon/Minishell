/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:48:45 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/18 13:24:21 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_new_pwd(t_minishell *ms, char *oldpwd)
{
	
}

void	ft_cd(t_minishell *ms, char **str)
{
	if (str[0] && str[1])
	{
		ms->exit_status = 1;
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2));
	}
	set_new_pwd(ms, "OLDPWD");
}
/*
void	cd_update(void)
{
}

void	cd_error(void)
{	
}

int	check_home( t_minishell *ms, char *str, char **tmp)
{
	t_envlist	*env;

	if (!str)
	{
		env = check_env("HOME", ms->explist);
		if (!env)
		{
			cd_error(); // HACER
			return (1);
		}
		chdir(env->value);
		return (0);
	}
	return (-1);
}

void	ft_cd(t_minishell *ms, char *str)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(sizeof(char *), 3);
	tmp[0] = getcwd(tmp[0], 0);
	i = check_home(ms, str, tmp);
	if (!tmp[0])
		tmp[0] = ft_strdup(str);
	if (i > 0)
		return ;
	else if (i < 0)
	{
		if (ft_strlen(str) == 1 && str[0] == '/')
			tmp[1] = ft_strdup("/\0");
		else
			tmp[1] = ft
	}
	ms->exit_status = 0;
	cd_update(); //HACER
}

*/