/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:50:02 by vicrodri          #+#    #+#             */
/*   Updated: 2023/07/31 13:09:11 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, ft_strlen(s1));
	ft_memcpy(result + ft_strlen(s1), s2, ft_strlen(s2));
	ft_bzero(result + (ft_strlen(s1) + ft_strlen(s2)), 1);
	return (result);
}

// int	main(void)
// {
// 	char *s1 = "lorem ipsum";
// 	char *s2 = "dolor sit amet";
// 	printf("%s", ft_strjoin(s1, s2));
// 	free(ft_strjoin(s1, s2));
// 	system("leaks a.out");
// }

/*Reserva (con malloc(3)) y devuelve una nueva string, formada por la 
concatenación de ’s1’ y ’s2’.

Devuelve la nueva string. NULL si falla la reserva de memoria.*/