/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:28 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/24 18:47:52 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer_init(char *input, t_token *token)
{
	int		i;
	int		j;
	int		type;

	i = -1;
	j = 0;
	while (input[++i] != '\0')
	{
		type = type_token(input[i]);
		if ((type == CHAR_GREAT || type == CHAR_LESS) && \
			token->status == NO_QUOTE)
			token = redirect_token(token, input, &j, &i);
		else if (type == CHAR_NORMAL)
			token->str[j++] = input[i];
		else if (type == CHAR_SPACE && j > 0 && token->status == NO_QUOTE)
		{
			token->join_next = 0;
			token = new_token(token, ft_strlen(input) - i);
			j = 0;
		}
		else
			token = other_tokens(token, type, &j, ft_strlen(input) - i);
	}
}

void	free_lexer(t_lexer *lexer)
{
	t_token	*token;
	t_token	*next;

	if (!lexer)
		return ;
	token = lexer->token_list;
	while (token != NULL)
	{
		next = token->next;
		free_token(token);
		token = next;
	}
	free(lexer);
}

int	lexer_files(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type > 59 && tmp->type < 66 && \
			(!tmp->next || tmp->next->type != -1))
		{
			ft_putstr_fd("No filename given\n", 2);
			return (1);
		}
		if (tmp->type == CHAR_LESS)
			tmp->next->type = INFILE;
		if (tmp->type == CHAR_GREAT)
			tmp->next->type = OUTFILE;
		if (tmp->type == CHAR_LESSLESS)
			tmp->next->type = DELIMITER;
		if (tmp->type == CHAR_GREATGREAT)
			tmp->next->type = OUTFILE_APPEND;
		tmp = tmp->next;
	}
	return (0);
}

int	count_tokens(t_lexer *lexer)
{
	t_token	*tmp;
	int		i;

	tmp = lexer->token_list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	lexer->n_tokens = i;
	return (i);
}
