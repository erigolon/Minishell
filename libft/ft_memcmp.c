/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:49:10 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:14:14 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (i < n)
	{
		if ((unsigned char)a[i] != (unsigned char)b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	int i;

// 	printf("%d\n", memcmp("abc", "abc", 7));

// 	i = ft_memcmp("abc", "abc", 7);
// 	printf("%d\n", i);
// }

/*The memcmp() function compares byte string s1 against byte string s2.
Both strings are assumed to be n bytes long.

The	memcmp(void) function returns zero if the two strings are identical,
otherwise returns the difference between the first two differing bytes
(treated as unsigned char values, so that `\200' is greater than `\0',
for example).  Zero-length strings are always identical.  This behavior
is not required by C and portable code should only depend on the sign of
the returned value.*/