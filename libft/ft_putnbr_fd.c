/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:43:43 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 12:55:28 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <fcntl.h>
// #include <stdio.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	nb = n;
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		nb %= 10;
	}
	c = nb + '0';
	write(fd, &c, 1);
}

// int	main(void)
// {
// 	int n;
// 	char *a;

// 	int fd, sz;
// 	n = 485;
// 	a = (char *)calloc(100, sizeof(char));
// 	fd = open("hola.txt", O_RDWR);
// 	ft_putnbr_fd(n, fd);
// 	sz = read(fd, a, 10);
// 	printf("It returned %d\n", sz);
// 	a[sz] = '\0';
// 	int close(int fd);
// }

/*Envía el número ’n’ al file descriptor dado.*/