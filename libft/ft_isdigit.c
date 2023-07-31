/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:09:56 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:13:45 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*int	main(void)
{
	int c = 51;
	printf("%d\n", isdigit(c));
	printf("%d\n", ft_isdigit(c));
}*/

/*The isdigit() function tests for a decimal digit character.The value of the 
argument must be representable as an unsigned char or the value of EOF.

The	isdigit(void) afunction return zero if the character tests
false and return non-zero if the character tests true.*/