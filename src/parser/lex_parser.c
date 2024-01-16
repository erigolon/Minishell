/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:12:32 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/16 18:19:38 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lex_parser(t_minishell *ms, char *prompt)
{
	if (prompt == NULL || ft_strlen(prompt) == 0)
		return ;
	ms->input = ft_splitms(prompt, ' ', 0, 0);
	ft_expander(ms);
	ft_parser(ms);
}
