/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:24 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/22 17:23:22 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

t_lexer	*lex_parser(t_minishell *ms, char *prompt)
{
	t_lexer	*lexer;

	if (prompt == NULL || ft_strlen(prompt) == 0)
		return(0) ;
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->error = 0;
	lexer->token_list = new_token(NULL, ft_strlen(prompt));
	lexer_init(prompt, lexer->token_list);
	if (close_quotes(lexer->token_list))
		lexer->error = 1;
	remove_empty_tokens(lexer);
	if (lexer_files(lexer->token_list))
		lexer->error = 1;
	trim_quotes_token(lexer->token_list);
	expand_all_wildcards(lexer);
	lexer->token_list = expand_tokens(lexer, ms);
	remove_empty_tokens(lexer);
	join_dollars(lexer->token_list);
	join_tokens(lexer->token_list);
	replace_tilde(lexer->token_list, ms);
	count_tokens(lexer);
	return (lexer);
}
