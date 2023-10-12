/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:25:30 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/05 20:10:27 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

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
			while ((s[i] != '\'' && s[i] != 34) && s[i] != 0)
					i++;
			if (s[i] == '\'' || s[i] == 34)
			{	
				i++;
				n++;
			}
		}
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			n++;
		i++;
	}
	printf("n = %d\n", n);
	return (n);
}
// arreglar los dobles cmd

int	ft_strcontcmd(char const *s, char c)
{
	int	i;
	int	n;
	int cmd;

	n = 0;
	i = 0;
	cmd = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c) && !(s[i - 1] == ' '
				&& (s[i + 1] == ' ' || s[i + 1] == '\0')))
		{
			n++;
			if (s[i - 1] != ' ' && s[i + 1]!= '\0' && s[i + 1] != ' ' && i > 0)
				n++;
			if(s[i + 1] == c)
				i++;
		}
		i++;
	}
	printf("n = %d\n", n);
	return (n);
}

char	*ft_wordpipex(char const *str, char s)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] != s && str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != 0)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (0);
	word[i] = 0;
	i = 0;
	while (str[i] != s && str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != 0)
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
char	*ft_wordcmd(char const *str, char s)
{
	char	*word;

	if (str[0] == s && str[1] == s)
	{	
		word = ft_calloc(3, sizeof(char));
		word[2] = 0;
		word[0] = s;
		word[1] = s;
	}
	else
	{
		word = ft_calloc(2, sizeof(char));
		word[1] = 0;
		word[0] = s;
	}
	return (word);
}

char	**ft_splitms(char const *str, char c)
{
	char	**split;
	int		word;
	int		i;
	int		com;

	word = 0;
	i = 0;
	split = ft_calloc((ft_strcontpipex(str, c)
				+ ft_strcontcmd(str, '<') + ft_strcontcmd(str, '>')
				+ ft_strcontcmd(str, '|') + 1),
			sizeof(char *));
	if (!split)
		return (0);
	while (str[i] != 0)
	{
		while (str[i] == c && str[i] != 0)
			i++;
		if (str[i] == '\'' || str[i] == 34)
		{
			com = str[i];
			split[word++] = ft_wordpipexcom(&str[i++]);
			while ((str[i] != com) && str[i] != 0)
				i++;
			if (str[i] == com)
				i++;
			// while (str[i] != c && str[i] != '<' && str[i] != 0)
			// i++;
		}
		else if (str[i] == '<')
		{
			split[word++] = ft_wordcmd(&str[i++], '<');
			if(str[i] == '<')
				i++;
		}	
		else if (str[i] == '>')
		{
			split[word++] = ft_wordcmd(&str[i++], '>');
			if(str[i] == '>')
				i++;
		}	
		else if (str[i] == '|')
		{
			split[word++] = ft_wordcmd(&str[i++], '|');
			if(str[i] == '|')
				i++;
		}	
		else if (str[i] != c && str[i] != 0)
		{	
			split[word++] = ft_wordpipex(&str[i], c);
			while (str[i] != c && str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != 0)
			i++;
		}
	}
	return (split);
}
