/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:24:50 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:14:23 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*str;
	unsigned char		*result;

	i = 0;
	str = (unsigned char *)src;
	result = (unsigned char *)dst;
	if (dst == src || !n)
		return (dst);
	while (i < n)
	{
		result[i] = str[i];
		i++;
	}
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
// 	ft_memcpy(ptr2, src, n);
// 	printf("%s\n", ptr2);

// 	memcpy(ptr, src, n);
// 	printf("%s\n", ptr);
// }

/*The memcpy() function copies n bytes from memory area src to memory area
dst.  If dst and src overlap, behavior is undefined.  Applications in
which dst and src might overlap should use	memmove(3) instead.

The	memcpy(void) function returns the original value of dst.*/