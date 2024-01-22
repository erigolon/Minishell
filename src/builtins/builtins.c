/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:14:11 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/22 17:06:44 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_minishell *ms)
{
	char	*dir;

	(void) ms;
	dir = NULL;
	dir = getcwd(dir, 0);
	ft_printf("%s\n", dir);
	free(dir);
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

