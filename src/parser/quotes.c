/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:42 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/24 18:49:45 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_quotestrim(t_token *token)
{
	char	*tmp;

	while (token)
	{
		if ((token->status == CHAR_SQUOTE || token->status == CHAR_DQUOTE) && \
			token->type != DELIMITER)
		{
			tmp = ft_substr(token->str, 1, ft_strlen(token->str) - 2);
			free(token->str);
			token->str = tmp;
		}
		token = token->next;
	}
}

t_token	*quote_token(t_token *tok, int type, int *j, int len)
{
	if (*j > 0 && (tok->str[0] != CHAR_DQUOTE && tok->str[0] != CHAR_SQUOTE))
	{
		tok = new_token(tok, len);
		*j = 0;
	}
	tok->str[(*j)++] = type;
	tok->status = DOUBT_QUOTE;
	if (*j > 1 && tok->str[0] == type)
	{
		tok->status = type;
		tok->str[*j] = '\0';
		*j = 0;
		tok = new_token(tok, len);
	}
	return (tok);
}

int	close_quotes(t_token *tok)
{
	int		flag;
	int		len;
	char	open_quote;

	flag = 0;
	while (tok)
	{
		if (tok->str[0] == CHAR_SQUOTE || tok->str[0] == CHAR_DQUOTE)
		{
			open_quote = tok->str[0];
			len = ft_strlen(tok->str);
			if ((len > 0 && tok->str[len - 1] != open_quote) || len == 1 || \
				tok->status == DOUBT_QUOTE)
				flag = 1;
		}
		tok = tok->next;
	}
	if (flag)
	{
		ft_putstr_fd("minishell: syntax error: unmatched quotes\n", 2);
		return (1);
	}
	return (0);
}
