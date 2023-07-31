/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:33:39 by vicrodri          #+#    #+#             */
/*   Updated: 2023/07/10 17:38:57 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

// int	main(void)
// {
// 	char cadena[] = "holaaa";

// 	printf("%lu\n", strlen(cadena));
// 	printf("%lu\n", ft_strlen(cadena));
// }

/*The strlen() function computes the length of the string s.  The strnlen()
function attempts to compute the length of s, but never scans beyond the
first maxlen bytes of s.

The strlen() function returns the number of characters that precede the
terminating NUL character.  The strnlen() function returns either the
same result as strlen() or maxlen, whichever is smaller.*/