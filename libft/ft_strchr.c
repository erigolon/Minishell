/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:47:34 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:14:49 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (((char *)s)[i] != '\0')
	{
		if (((char *)s)[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (((char *)s)[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

// int	main(void)
// {
// 	char *str = "hola";
// 	int c = 'o';
// 	printf("%s\n", ft_strchr(str, c));
// }

/*The strchr() function locates the first occurrence of c (converted to a
char) in the string pointed to by s.  The terminating null character is
considered to be part of the string; therefore if c is `\0', the functions
locate the terminating `\0'.
 
The functions strchr() and strrchr() return a pointer to the located
character, or NULL if the character does not appear in the string.*/