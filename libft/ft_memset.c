/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:42:38 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:14:41 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	b;
	unsigned char	*str;

	i = 0;
	b = c;
	str = (unsigned char *) s;
	while (i < n)
	{
		str[i] = b;
		i++;
	}
	return (str);
}

// int	main(void)
// {
// 	char str[50] = "Hola a todos";
// 	printf("\nBefore memset(): %s\n", str);
// 	ft_memset(str, '.', 7 * sizeof(char));
// 	printf("After memset():  %s", str);
// }

/*The memset() function writes len bytes of value c (converted to an
unsigned char) to the string b.

The memset() function returns its first argument.*/