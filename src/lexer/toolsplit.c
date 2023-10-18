/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:19:36 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/17 21:34:21 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
