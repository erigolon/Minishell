/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:37:50 by erigolon          #+#    #+#             */
/*   Updated: 2023/09/27 12:32:25 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_minishell *ms)
{
	t_envlist	*lst;

	lst = ms->explist;
	while (lst)
	{
		printf("declare -x %s=%s\n", lst->env, lst->value);
		lst = lst->next;
	}
}
