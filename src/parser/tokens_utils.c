/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:48 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/24 18:41:46 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	type_token(char c)
{
	if (c == '|')
		return (CHAR_PIPE);
	if (c == '\'')
		return (CHAR_SQUOTE);
	if (c == '\"')
		return (CHAR_DQUOTE);
	if (c == ' ')
		return (CHAR_SPACE);
	if (c == '>')
		return (CHAR_GREAT);
	if (c == '<')
		return (CHAR_LESS);
	if (c == 0)
		return (CHAR_NULL);
	if (c == '~')
		return (CHAR_TILDE);
	return (CHAR_NORMAL);
}

t_token	*new_token(t_token *token, int size)
{
	if (token == NULL)
	{
		token = ft_calloc(1, sizeof(t_token));
		token->prev = NULL;
	}
	else
	{
		token->next = ft_calloc(1, sizeof(t_token));
		token->next->prev = token;
		token = token->next;
	}
	token->str = ft_calloc(size + 1, sizeof(char));
	token->type = CHAR_NORMAL;
	token->status = NO_QUOTE;
	token->escaped = NORMAL;
	token->join_next = 1;
	token->next = NULL;
	return (token);
}

void	free_token(t_token *token)
{
	if (token->prev && token->next)
	{
		token->prev->next = token->next;
		token->next->prev = token->prev;
	}
	else if (token->prev)
		token->prev->next = NULL;
	else if (token->next)
		token->next->prev = NULL;
	if (token->str)
		free(token->str);
	if (token)
		free(token);
}

void	remove_empty_tokens(t_lexer *lexer)
{
	t_token	*tok;
	t_token	*prev;
	t_token	*tmp;

	tok = lexer->token_list;
	prev = NULL;
	while (tok)
	{
		if (tok->str && tok->str[0] == '\0' && tok->status == NO_QUOTE)
		{
			if (prev)
				prev->next = tok->next;
			else
				lexer->token_list = tok->next;
			tmp = tok->next;
			free_token(tok);
			tok = tmp;
		}
		else
		{
			prev = tok;
			tok = tok->next;
		}
	}
}
