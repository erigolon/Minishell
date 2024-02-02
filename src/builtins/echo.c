/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:43:29 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/30 11:06:20 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(char **str)
{
	int	line;
	int	i;

	i = 0;
	line = 1;
	if (str[i])
	{
		while (check_n(str[i]))
		{
			line = 0;
			i++;
		}
		while (str[i])
		{
			printf("%s", str[i]);
			i++;
			if (str[i])
				printf(" ");
		}
	}
	if (line)
		printf("\n");
}
