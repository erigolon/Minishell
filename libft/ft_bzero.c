/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:56:42 by vicrodri          #+#    #+#             */
/*   Updated: 2023/07/11 15:59:13 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

// int	main(void)
// {
// 	size_t n;

// 	char s[6] = "holsda";
// 	n = 3;

// 	printf("%s\n", s);
// 	ft_bzero(s, 3);
// 	printf("%c\n", s[0]);
// 	printf("%i\n", s[1]);
// 	printf("%i\n", s[2]);
// 	printf("%i\n", s[3]);
// 	printf("%i\n", s[4]);
// 	printf("%i\n", s[5]);
// }

/*The bzero() function writes n zeroed bytes to the string s.  If n is
zero, bzero() does nothing*/