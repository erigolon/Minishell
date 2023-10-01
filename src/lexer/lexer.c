/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:32:08 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/27 20:23:46 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

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


void	ft_tokenizer(char *input, t_minishell *minishell)
{
	minishell->input = ft_splitpipex(input, ' ');
	ft_expander(*minishell);
	ft_parser(*minishell);

}