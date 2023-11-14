/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:12:28 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/23 18:01:16 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoinizq(char const *s1, char const *s2)
{
	char	*result;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, ft_strlen(s1));
	ft_memcpy(result + ft_strlen(s1), s2, ft_strlen(s2));
	ft_bzero(result + (ft_strlen(s1) + ft_strlen(s2)), 1);
	free((char *)s1);
	// free((char *)s2);
	return (result);
}


char	*ft_strjoinder(char const *s1, char const *s2)
{
	char	*result;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, ft_strlen(s1));
	ft_memcpy(result + ft_strlen(s1), s2, ft_strlen(s2));
	ft_bzero(result + (ft_strlen(s1) + ft_strlen(s2)), 1);
	// free((char *)s1);
	free((char *)s2);
	return (result);
}

int	ft_strcontpipex(char const *s, char c)
{
	int		i;
	int		n;
	char	tmp;

	n = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == 34)
		{
			tmp = s[i];
			i++;
			while ((s[i] != tmp) && s[i] != 0)
					i++;
			if (s[i] == tmp)
			{	
				i++;
				n++;
			}
		}
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			n++;
		i++;
	}
	return (n);
}

int	ft_strcontcmd(char const *s, char c)
{
	int	i;
	int	n;
	int	cmd;

	n = 0;
	i = 0;
	cmd = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c) && !(s[i - 1] == ' '
				&& (s[i + 1] == ' ' || s[i + 1] == '\0')))
		{
			n++;
			if (s[i - 1] != ' ' && s[i + 1] != '\0' && s[i + 1] != ' ' && i > 0)
				n++;
			if (s[i + 1] == c)
				i++;
		}
		i++;
	}
	return (n);
}