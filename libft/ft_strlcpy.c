/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:14:44 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:15:38 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (src[count] != '\0')
		count++;
	if (dst != NULL && dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (count);
}

// int	main(void)
// {
// 	unsigned int i;
// 	unsigned int j;
// 	char dest[10];
// 	char src[] = "wdfjbhhu";
// 	j = ft_strlcpy(dest, src, 2);
// 	printf("%d\n", j);
// 	printf("%s\n", dest);

// 	i = ft_strlcpy(dest, src, 2);
// 	printf("%d\n", i);
// 	printf("%s\n", dest);
// }

/*strlcpy() copies up to dstsize - 1 characters from the string src to dst,
NUL-terminating the result if dstsize is not 0.*/