/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:14:21 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/30 10:42:58 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd_update(t_minishell *ms, char **dir)
{
	t_envlist	*old;
	t_envlist	*pwd;
	char		**export;

	export = ft_calloc(sizeof(char *), 4);
	old = check_env("OLDPWD", ms->explist);
	pwd = check_env("PWD", ms->explist);
	if (!old)
		export[0] = ft_strdup("");
	else if (pwd)
		export[0] = ft_strjoin("OLDPWD=", pwd->value);
	else
		export[0] = ft_strjoin("OLDPWD", dir[0]);
	if (pwd)
	{
		export[3] = NULL;
		export[3] = getcwd(export[3], 0);
		export[1] = ft_strjoin("PWD=", export[3]);
	}
	ft_export(ms, export);
	free_str(export, 0);
	free_str(dir, 0);
}

int	check_home( t_minishell *ms, char *str, char **tmp)
{
	t_envlist	*env;

	if (!str)
	{
		env = check_env("HOME", ms->explist);
		if (!env)
		{
			ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
			ms->exit_status = 1;
			free_str(tmp, 0);
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
		if (chdir(tmp[1]) && chdir(str))
		{
			ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
			ms->exit_status = 1;
			free_str(tmp, 0);
			return ;
		}
	}
	ms->exit_status = 0;
	cd_update(ms, tmp);
}
