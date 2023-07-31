/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:14:25 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:14:05 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	b;
	unsigned char	*str;

	i = 0;
	b = c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == b)
		{
			return ((void *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char *s;
// 	int c;
// 	int n;
// 	s = "holahola";
// 	c = 'a';
// 	n = 4;
// 	printf("%s\n", memchr(s, c, n));
// 	printf("%s\n", ft_memchr(s, c, n));
// }

/*The memchr() function locates the first occurrence of c (converted to an
unsigned char) in string s.

The	memchr(void) function returns a pointer to the byte located, or NULL if
no such byte exists within n bytes.*/