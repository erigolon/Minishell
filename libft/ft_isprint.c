/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:30:48 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:13:54 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// int	main(void)
// {
// 	int c = 128;
// 	printf("%d\n", isprint(c));
// 	printf("%d\n", ft_isprint(c));
// }

/*The isprint() function tests for any printing character, including space
(` ').  The value of the argument must be representable as an unsigned
char or the value of EOF.

The	isprint(void) function returns zero if the character tests false and
returns non-zero if the character tests true.*/