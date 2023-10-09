/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:34:32 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/05 10:40:19 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_minishell *ms)
{
	t_envlist	*lst;

	lst = ms->envlist;
	while (lst)
	{
		if (lst->value)
			printf("%s=%s\n", lst->env, lst->value);
		lst = lst->next;
	}
}
