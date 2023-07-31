/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:42:13 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:16:18 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (!set || !s1)
		return (NULL);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	while (j >= 0 && ft_strchr(set, s1[j]))
		j--;
	result = ft_substr(s1, i, j - i + 1);
	return (result);
}

// int	main(void)
// {
// 	char *s1 = "sacos";
// 	char *set = "sacos";
// 	printf("%s", ft_strtrim(s1, set));
// }

/*Elimina todos los caracteres de la string ’set’ desde el principio y desde 
el final de ’s1’, hasta encontrar un caracter no perteneciente a ’set’. La
string resultante se devuelve con una reserva de	malloc(3)*/