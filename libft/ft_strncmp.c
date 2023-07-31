/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:10:38 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:15:53 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char *s1;
// 	char *s2;
// 	int i;
// 	unsigned int n = 3;
// 	s1 = "halasfd3";
// 	s2 = "halasfd7";
// 	printf("%d\n", strncmp(s1, s2, n));

// 	i = ft_strncmp(s1, s2, n);
// 	printf("%d\n", i);
// }

/*Thestrncmp() function lexicographically compare the null-terminated strings 
s1 and s2.
The strncmp() function compares not more than n characters.  Because
strncmp() is designed for comparing strings rather than binary data,
characters that appear after a `\0' character are not compared.

The strncmp() function return an integer greater than,equal to, or less
than 0, according as the string s1 is greater than,
equal to, or less than the string s2.  The comparison is done using
unsigned characters, so that `\200' is greater than `\0'.*/