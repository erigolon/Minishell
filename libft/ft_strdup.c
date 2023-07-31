/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:47:00 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:15:12 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while ((char)src[i] != '\0')
	{
		dest[i] = (char)src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// int	main(void)
// {
// 	char *src;

// 	src = "hola";
// 	printf("%s\n", strdup(src));
// 	printf("%s\n", ft_strdup(src));
// 	free()
// }

/*The strdup() function allocates sufficient memory for a copy of the string 
s1, does the copy, and returns a pointer to it.  The pointer may subsequently
be used as an argument to the function	free(3). If insufficient memory is 
available, NULL is returned and errno is set to ENOMEM.*/