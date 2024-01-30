/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:03:23 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/25 18:59:42 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_str(char **str, int i)
{
if (!str)
		return ;
	if (!i)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str[i]);
	}
	else
	{
		while (i >= 0)
		{
			free(str[i]);
			i--;
		}
	}
	free(str);
}

char	**ft_strddup(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!*envp)
		return (NULL);
	while (envp[i])
		i++;
	tmp = ft_calloc(sizeof(char *), i + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		if (!tmp[i])
		{
			free_str(tmp, i);
			return (NULL);
		}
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}
