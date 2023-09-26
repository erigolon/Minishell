/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:32:08 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/26 17:01:19 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

size_t	ft_strlenenv(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=')
		i++;
	return (i);
}

void	ft_expander(t_minishell minishell)
{
	int	i;
	int	j;
	int k;
	
	i = 0;
	while (minishell.input[i])
	{
		j = 0;
		while (minishell.input[i][j])
		{
			if (minishell.input[i][j] == '$'
				&& minishell.input[i][j - 1] != '\'')
			{
				k = 0;
				while (minishell.envp[k])
				{
					if (ft_strncmp(minishell.envp[k], &minishell.input[i][j + 1],
						ft_strlenenv(minishell.envp[k])) == 0)
						ft_memmove(&minishell.input[i][j],
							&minishell.envp[k][ft_strlenenv(minishell.envp[k]) + 1],
							ft_strlen(minishell.envp[k]) - 
							ft_strlenenv(minishell.envp[k]) + 1);
					k++;
				}
			}
		j++;
	}
		i++;
	}
	//pendiente de arreglar lo del expander (hacer funcion con strjoin para comillas dobles), pasar a ver el parseo, y subir al test. 
}

void ft_token_add_back(t_token **token, t_token *new)
{
	t_token *aux;


	if (!new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	aux = *token;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
	printf("aux->next->str = %s\n", aux->next->str);
}

t_token	*new_token(t_token *token, char	*input)
{
	t_token	*new;
	
	new = ft_calloc(1, sizeof(t_token));
	new->str = ft_strdup(input);
	new->next = NULL;

	return (token);
}


t_lexer	*ft_tokenizer(char *input, t_minishell *minishell)
{
    t_lexer	*lexer;
	int i;

	i = 0;
	if (input == NULL || ft_strlen(input) == 0)
		return (0);
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->error = 0;
	minishell->input = ft_splitpipex(input, ' ');
	ft_expander(*minishell);
		printf("lexer->token_list->str = %s\n", minishell->input[0]);
	printf("lexer->token_list->str = %s\n", minishell->input[1]);
	printf("lexer->token_list->str = %s\n", minishell->input[2]);
	printf("lexer->token_list->str = %s\n", minishell->input[3]);
	printf("lexer->token_list->str = %s\n", minishell->input[4]);
	
	printf("lexer->token_list->str = %s\n", minishell->input[5]);
	printf("lexer->token_list->str = %s\n", minishell->input[6]);
printf("lexer->token_list->str = %s\n", minishell->input[7]);
printf("lexer->token_list->str = %s\n", minishell->input[8]);
	// while (minishell->input[i])
	// {
	// 	ft_token_add_back(&lexer->token_list, new_token(lexer->token_list, minishell->input[i]));
	// 	printf("lexer->token_list->str = %s\n", lexer->token_list->str);
	// 	i++;
	// }
    return (lexer);
}