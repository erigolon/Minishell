/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:14:11 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/17 21:41:13 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_echo_n(char **str, int nl);

void	ft_exit_ms(t_minishell *ms, char **num)
{
	char	*msg;

	ft_putstr_fd("exit\n", 2);
	if (num && num[0])
	{
		if (!ft_check_exit(ms, num[0]))
		{
			msg = ft_strjoin_va(\
			"minishell: exit: %s: numeric argument required\n", num[0]);
			ft_putstr_fd(msg, 2);
			free(msg);
			ms->exit_status = 255;
		}
		else if (num[1])
		{
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			ms->exit_status = 1;
			return ;
		}
	}
	ms->exit = 0;
}

void	ft_pwd(t_minishell *ms)
{
	char	*dir;

	(void) ms;
	dir = NULL;
	dir = getcwd(dir, 0);
	ft_printf("%s\n", dir);
	free(dir);
}

void	ft_echo(char **str)
{
	int	i;
	int	j;
	int	nl;

	nl = 1;
	i = -1;
	while (str[++i])
	{
		j = 0;
		if (str[i][j] != '-')
			break ;
		while (++j && str[i][j] == 'n')
			nl = 0;
		if (str[i][j])
		{
			if (!i)
				nl = 1;
			break ;
		}
	}
	ft_echo_n(&str[i], nl);
}

static void	ft_echo_n(char **str, int nl)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printf("%s", str[i]);
		if (str[++i])
			ft_printf(" ");
	}
	if (nl)
		ft_printf("\n");
}
