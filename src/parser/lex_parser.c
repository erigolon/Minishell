/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:24 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/24 19:26:23 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	join_tokens(t_token *tk)
{
	char	*tmp_str;

	while (tk)
	{
		while (tk->next && tk->join_next && \
			(tk->type == CHAR_NORMAL || tk->type == CHAR_TILDE) && \
			(tk->next->type == CHAR_NORMAL || tk->next->type == CHAR_TILDE))
		{
			tmp_str = ft_strjoin(tk->str, tk->next->str);
			free(tk->str);
			tk->join_next = tk->next->join_next;
			tk->str = tmp_str;
			free_token(tk->next);
		}
		tk = tk->next;
	}
}

void	join_dollars(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		if (token->str && token->str[0] == '$' && ft_strlen(token->str) == 1 \
			&& token->next && token->join_next)
		{
			tmp = token;
			token = token->next;
			free_token(tmp);
			if (!token)
				return ;
		}
		token = token->next;
	}
}

t_lexer	*lex_parser(t_minishell *ms, char *prompt)
{
	t_lexer	*lexer;

	if (prompt == NULL || ft_strlen(prompt) == 0)
		return (0);
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->error = 0;
	lexer->token_list = new_token(NULL, ft_strlen(prompt));
	lexer_init(prompt, lexer->token_list);
	if (close_quotes(lexer->token_list))
		lexer->error = 1;
	remove_empty_tokens(lexer);
	if (lexer_files(lexer->token_list))
		lexer->error = 1;
	ft_quotestrim(lexer->token_list);
	lexer->token_list = expand_tokens(lexer, ms);
	remove_empty_tokens(lexer);
	join_dollars(lexer->token_list);
	join_tokens(lexer->token_list);
	ft_expander_directory(lexer->token_list, ms);
	count_tokens(lexer);
	return (lexer);
}
