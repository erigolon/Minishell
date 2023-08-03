/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitpipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:25:30 by vicrodri          #+#    #+#             */
/*   Updated: 2023/08/03 16:39:41 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	ft_strcontpipex(char const *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == 34)
		{
			i++;
			while ((s[i] != '\'' || s[i] != 34) && s[i] != 0)
				i++;
			if (s[i++] == '\'' || s[i] == 34)
				n++;
		}
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			n++;
		i++;
	}
	return (n);
}

char	*ft_wordpipex(char const *str, char s)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] != s && str[i] != 0)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (0);
	word[i] = 0;
	i = 0;
	while (str[i] != s && str[i] != 0)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

char	*ft_wordpipexcom(char const *str)
{
	int		i;
	char	*word;
	int		com;

	com = str[0];
	i = 1;
	while (str[i] != 0 && str[i] != com)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (0);
	word[i] = 0;
	i = 0;
	word[i] = str[i];
	i++;
	while (str[i] != 0 && str[i] != com)
	{
		word[i] = str[i];
		i++;
	}
	if (str[i] == com)
		word[i] = str[i];
	return (word);
}

char	**ft_splitpipex(char const *str, char c)
{
	char	**split;
	int		word;
	int		i;

	word = 0;
	i = 0;
	split = ft_calloc((ft_strcontpipex(str, c) + 1), sizeof(char *));
	if (!split)
		return (0);
	while (str[i] != 0)
	{
		while (str[i] == c && str[i] != 0)
			i++;
		if (str[i] == '\'' || str[i] == 34)
		{
			split[word++] = ft_wordpipexcom(&str[i++]);
			while ((str[i] != '\'' || str[i] != 34) && str[i] != 0)
				i++;
		}
		else if (str[i] != c && str[i] != 0)
			split[word++] = ft_wordpipex(&str[i], c);
		while (str[i] != c && str[i] != 0)
			i++;
	}
	return (split);
}
