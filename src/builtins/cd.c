/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:14:21 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/17 21:44:57 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_cd_error(char *str, t_minishell *ms, int err, char **to_free);
static void	ft_cd_update(t_minishell *ms, char **dir);
static int	ft_check_home(char *str, char **tmp, t_minishell *ms);


double	ft_power_double(double n, int pov)
{
	int	i;
	int	num;

	i = -1;
	num = 1;
	if (n < 0)
		n *= -1;
	while (++i < pov)
		num *= 10;
	return (n * num);
}

void	ft_cd(char *str, t_minishell *ms)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(sizeof(char *), 3);
	tmp[0] = getcwd(tmp[0], 0);
	i = ft_check_home(str, tmp, ms);
	if (!tmp[0])
		tmp[0] = ft_strdup(str);
	if (i > 0)
		return ;
	else if (i < 0)
	{
		if (ft_strlen(str) == 1 && str[0] == '/')
			tmp[1] = ft_strdup("/\0");
		else
			tmp[1] = ft_strjoin_va("%s/%s", tmp[0], str);
		if (chdir(tmp[1]) && chdir(str))
		{
			ft_cd_error(str, ms, 1, tmp);
			return ;
		}
	}
	ms->exit_status = 0;
	ft_cd_update(ms, tmp);
}

static int	ft_check_home(char *str, char **tmp, t_minishell *ms)
{
	t_envlist	*lst;

	if (!str)
	{
		lst = ft_getenv("HOME", ms->explist);
		if (!lst)
		{
			ft_cd_error(str, ms, 0, tmp);
			return (1);
		}
		chdir(lst->value);
		return (0);
	}
	return (-1);
}

static void	ft_cd_error(char *str, t_minishell *ms, int err, char **to_free)
{
	char		*tmp;
	struct stat	st;

	if (!err)
		ft_putstr_fd("minishell: cd: HOME: not set\n", 2);
	else
	{
		stat(str, &st);
		if (!S_ISREG(st.st_mode) && S_ISDIR(st.st_mode))
			tmp = ft_strjoin_va(
					"minishell: cd: %s: Permission denied\n", str);
		else if (!S_ISDIR(st.st_mode) && !access(str, F_OK))
			tmp = ft_strjoin_va(
					"minishell: cd: %s: Not a directory\n", str);
		else if (ft_strlen(str) > 255)
			tmp = ft_strjoin_va(
					"minishell: cd: %s: File name too long\n", str);
		else
			tmp = ft_strjoin_va(
					"minishell: cd: %s: No such file or directory\n", str);
		ft_putstr_fd(tmp, 2);
		free(tmp);
	}
	ms->exit_status = 1;
	ft_free_array(to_free, 0);
}

static void	ft_cd_update(t_minishell *ms, char **dir)
{
	t_envlist	*old;
	t_envlist	*pwd;
	char		**to_export;

	to_export = ft_calloc(sizeof(char *), 4);
	old = ft_getenv("OLDPWD", ms->explist);
	pwd = ft_getenv("PWD", ms->explist);
	if (!old)
		to_export[0] = ft_strdup("");
	else if (pwd)
		to_export[0] = ft_strjoin_va("OLDPWD=%s", pwd->value);
	else
		to_export[0] = ft_strjoin_va("OLDPWD=%s", dir[0]);
	if (pwd)
	{
		to_export[3] = NULL;
		to_export[3] = getcwd(to_export[3], 0);
		to_export[1] = ft_strjoin_va("PWD=%s", to_export[3]);
		free(to_export[3]);
	}
	ft_export(to_export, ms);
	ft_free_array(to_export, 0);
	ft_free_array(dir, 0);
}
