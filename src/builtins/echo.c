/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:43:29 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/11 13:13:42 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(char **str)
{
	int	line;
	int	i;

	i = 0;
	line = 1;
	if ((str[i][0] == '-' && str[i][1] == 'n' && str[i][2] == '\0'))
		line = 0;
	if (line == 0)
		i = 1;
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
		if (str[i])
			printf(" ");
	}
	if (line)
	{
		printf("\n");
	}
}
/*
void	echo_test(void)
{
	char	*args1[] = {"Hello,", "world!", NULL};
	char 	*args2[] = {"-n", "Hello,", "world!", NULL};
	ft_echo(args2);
}
*/
