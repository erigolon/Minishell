/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:37:50 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/04 15:51:00 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_minishell *ms, char **str)
{
	t_envlist	*lst;

	lst = ms->explist;
	if (!str[0])
	{
		sort_envlst(&ms->explist);
		while (lst)
		{
			printf("declare -x %s", lst->env);
			if (lst->value)
				printf("=\"%s\"", lst->value);
			printf("\n");
			lst = lst->next;
		}
	}
	// Falta hacer parte que exporte la nueva variable
}
