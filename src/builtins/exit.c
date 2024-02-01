/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:29:00 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/30 12:24:51 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_minishell *ms, char **nb)
{
	ft_putstr_fd("exit\n", 2);
	if (nb && nb[0])
	{
		if (check_exit(nb[0]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			ms->exit_status = 255;
		}
		else if (nb[1])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			ms->exit_status = 1;
		}
	}
	ms->exit = 0;
}
