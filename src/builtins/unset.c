/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:03:09 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/11 11:36:40 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_minishell *ms, char **str)
{
	t_envlist	*tmp;
	int			i;
	int			status;

	i = 0;
	status = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (ft_strchr(str[i], '='))
		{
			ft_putstr_fd ("minishell: unset: not a valid identifier", 2);
			status = 1;
		}
		else
		{
			tmp = check_env(str[i], ms->envlist);
			delete_env(&tmp);
			tmp = check_env(str[i], ms->explist);
			delete_env(&tmp);
		}
		i++;
	}
	ms->exit_status = status;
}
