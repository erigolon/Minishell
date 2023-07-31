/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:57:49 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:14:33 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*result;

	i = 0;
	str = (unsigned char *)src;
	result = (unsigned char *)dst;
	if (str > result)
	{
		ft_memcpy(result, str, len);
	}
	else if (str < result)
	{
		while (len > 0)
		{
			result[len - 1] = str[len - 1];
			len--;
		}
	}
	else if (len == 0 || str == result)
		return (dst);
	dst = result;
	return (dst);
}

// int	main(void)
// {
// 	char c[16];
// 	char *ptr = c;
// 	char *ptr2 = c;
// 	char *src;
// 	int n;
// 	n = 3;
// 	src = "adios";
// 	ft_memmove(ptr2, src, n);
// 	printf("%s\n", ptr2);

// 	memmove(ptr, src, n);
// 	printf("%s\n", ptr);
// }

/*The memmove() function copies len bytes from string src to string dst.
The two strings may overlap; the copy is always done in a non-destructive
manner.

The	memmove(void) function returns the original value of dst.*/