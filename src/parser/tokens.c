/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:54 by erigolon          #+#    #+#             */
/*   Updated: 2024/02/01 10:52:33 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*other_tokens(t_token *tok, int type, int *j, int len)
{
	if (type == CHAR_SPACE && *j == 0 && tok->status == NO_QUOTE)
	{
		if (tok->prev && tok->prev->status != NO_QUOTE)
			tok->prev->join_next = 0;
		return (tok);
	}
	else if (type == CHAR_DQUOTE || type == CHAR_SQUOTE)
		return (quote_token(tok, type, j, len));
	else if (*j > 0 && tok->status == NO_QUOTE)
	{
		tok = new_token(tok, 2);
		*j = 0;
	}
	else if ((*j > 0 && tok->status != NO_QUOTE) || tok->type == CHAR_TILDE)
	{
		tok->str[(*j)++] = type;
		return (tok);
	}
	tok->str[0] = type;
	tok->type = type;
	*j = 0;
	tok = new_token(tok, len);
	return (tok);
}

t_token	*redirect_token(t_token *token, char *input, int *j, int *i)
{
	if (*j > 0 && token->status == NO_QUOTE)
	{
		token = new_token(token, ft_strlen(input) - *i);
		*j = 0;
	}
	if ((input[*i] == CHAR_GREAT && input[*i + 1] == CHAR_GREAT) || \
		(input[*i] == CHAR_LESS && input[*i + 1] == CHAR_LESS))
	{
		token->type = input[(*i)] + 3;
		token->str[(*j)++] = input[(*i)++];
		token->str[(*j)++] = input[(*i)];
		token->str[*j] = '\0';
	}
	else
	{
		token->str[(*j)++] = input[(*i)];
		token->str[*j] = '\0';
		token->type = input[(*i)];
		*j = 0;
	}
	token = new_token(token, ft_strlen(input) - *i);
	return (token);
}
