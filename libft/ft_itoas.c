/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:40:52 by vicrodri          #+#    #+#             */
/*   Updated: 2023/06/20 15:48:30 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lenint_c(long n)
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

char	*ft_itoa_c(int n)
{
	size_t	i;
	char	*result;
	long	nlon;

	nlon = (long)n;
	i = ft_lenint_c(nlon);
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

char	*ft_itoa_uc(unsigned int n)
{
	char	*result;
	size_t	i;
	long	nlon;

	nlon = n;
	i = ft_lenint_c(nlon);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (!result)
		return (0);
	result[i] = 0;
	if (nlon == 0)
		result[0] = '0';
	while (nlon > 0)
	{
		result[i - 1] = (char)((nlon % 10) + '0');
		i--;
		nlon = nlon / 10;
	}
	return (result);
}

size_t	ft_lenint_hexa(unsigned long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		i++;
		n = n / 16;
	}
	return (i);
}

char	*ft_itoa_hexa(unsigned long n)
{
	char	*result;
	size_t	i;
	char	*hex;

	hex = "0123456789abcdef";
	i = ft_lenint_hexa(n);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (!result)
		return (0);
	result[i] = 0;
	if (n == 0)
		result[0] = hex[n];
	while (n > 0)
	{
		result[i - 1] = hex[n % 16];
		i--;
		n = n / 16;
	}
	return (result);
}
