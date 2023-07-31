/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:16:12 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:13:04 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ctype.h>
#include <stdio.h>*/
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/*int	main(void)
{
	int c = 115;
	printf("%d\n", isalpha(c));
	printf("%d\n", ft_isalpha(c));
}*/

/*The isalpha() function tests for any character for which isupper(3) or
islower(3) is true.  The value of the argument must be representable as
an unsigned char or the value of EOF.

The	isalpha(void) function returns zero if the character tests false and
returns non-zero if the character tests true.*/