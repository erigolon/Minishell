/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:03:23 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/22 17:47:07 by erigolon         ###   ########.fr       */
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
char	**ft_copy_array(char **src, int add)
{
	int		i;
	char	**dest;

	i = 0;
	if (!*src)
		return (NULL);
	while (src[i])
		i++;
	dest = ft_calloc(sizeof(char *), i + 1 + add);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			free_str(dest, i);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	ft_del_items_array(char **str, int del)
{
	int	i;

	i = 0;
	if (del < 1)
		return ;
	while (str[i] && i < del)
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	i = 0;
	while (str[i + del])
	{
		str[i] = ft_strdup(str[i + del]);
		free (str[i + del]);
		i++;
	}
	str[i] = str[i + del];
	free (str[i + del]);
}
