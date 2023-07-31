/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:45:54 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:16:35 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

// int	main(void)
// {
// 	int c = 71;
// 	printf("%d\n", tolower(c));
// 	printf("%d\n", ft_tolower(c));
// }

/*The tolower() function converts an upper-case letter to the corresponding
lower-case letter.  The argument must be representable as an unsigned
char or the value of EOF.

If the argument is an upper-case letter, the tolower() function returns
the corresponding lower-case letter if there is one; otherwise, the argument 
is returned unchanged.*/