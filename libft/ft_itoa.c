/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:33:06 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/26 14:41:36 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

size_t	ft_lenint(long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*result;
	long	nlon;

	nlon = (long)n;
	i = ft_lenint(nlon);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	result[i] = 0;
	if (n < 0)
	{
		result[0] = '-';
		nlon = nlon * (-1);
	}
	if (nlon == 0)
		result[0] = 0 + '0';
	while (nlon > 0)
	{
		result[i - 1] = ((nlon % 10) + '0');
		nlon = nlon / 10;
		i--;
	}
	return (result);
}

// int	main(void)
// {
// 	int n = 0;
// 	char *result;
// 	result = ft_itoa(n);

// 	printf("%s", result);
// }

/*Converts an int variable to a string, using an extra function that counts the 
num of digits of the integer to perform the allocation of dynamic memory with 
malloc.
The array is filled from the last position to the first.
If a memory allocation error occurs, the function returns a null pointer.*/