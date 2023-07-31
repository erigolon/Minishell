/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:41:51 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:16:43 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

// int	main(void)
// {
// 	int	c;

// 	c = 125;
// 	printf("%d\n", toupper(c));
// 	printf("%d\n", ft_toupper(c));
// }

/*The toupper() function converts a lower-case letter to the corresponding
upper-case letter.  The argument must be representable as an unsigned
char or the value of EOF.

If the argument is a lower-case letter, the toupper() function returns
the corresponding upper-case letter if there is one; otherwise, the argument 
is returned unchanged.*/