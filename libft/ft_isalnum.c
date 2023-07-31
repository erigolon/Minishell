/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:22:10 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:12:54 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ctype.h>
// #include <stdio.h>
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*int	main(void)
{
	int c = 115;
	printf("%d\n", isalnum(c));
	printf("%d\n", ft_isalnum(c));
}*/

/*The isalnum() function tests for any character for which isalpha(3) or
isdigit(3) is true.  The value of the argument must be representable as
an unsigned char or the value of EOF.

The	isalnum(void) function returns zero if the character tests false and
returns non-zero if the character tests true.*/