/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:25:06 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/25 19:04:44 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*int	main(void)
{
	int c = 128;
	printf("%d\n", isascii(c));
	printf("%d\n", ft_isascii(c));
}*/

/* The isascii() function tests for an ASCII character, which is any character 
between 0 and octal 0177 inclusive.*/