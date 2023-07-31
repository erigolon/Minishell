/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:21:43 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:13:07 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "stdlib.h"
// #include "stdio.h"
#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	signo;

	num = 0;
	i = 0;
	signo = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signo *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num) * 10 + (str[i] - '0');
		i++;
	}
	return (signo * num);
}

// int main()
// {
// 	char *str;
//     int i;

//     str = "  -4521fhefue";
// 	printf("%d\n", atoi(str));
//     i = ft_atoi(str);
//     printf("%d\n", i);
//     return (0);
// }

/*The atoi() function converts the initial portion of the string pointed to
by str to int representation.*/
