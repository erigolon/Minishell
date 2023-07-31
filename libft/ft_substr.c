/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:12:25 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:16:26 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		i = ft_strlen(s) - start;
	else
		i = len;
	result = malloc(i + 1);
	if (!result || !s)
		return (NULL);
	ft_memcpy(result, (unsigned char *)s + start, i);
	ft_bzero((unsigned char *)result + (i), 1);
	return (result);
}

// int	main(void)
// {
// 	char *s = "01234";
// 	printf("%s", ft_substr(s, 10,10));
// }

/*Reserva (con malloc(3)) y devuelve una substring de la string ’s’.
La substring empieza desde el índice ’start’ y tiene una longitud máxima ’len’.

La substring resultante. NULL si falla la reserva de memoria.*/