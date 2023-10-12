/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:36:31 by vicrodri          #+#    #+#             */
/*   Updated: 2023/09/25 19:37:32 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <fcntl.h>
// #include <stdio.h>

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		write(fd, &s[i++], 1);
	write(fd, "\n", 1);
}

// int	main(void)
// {
// 	char	*c;
// 	char	*a;

// 	int fd, sz;
// 	c = "hola";
// 	a = (char *)calloc(100, sizeof(char));
// 	fd = open("hola.txt", O_RDWR);
// 	ft_putendl_fd(c, fd);
// 	sz = read(fd, a, 10);
// 	printf("It returned %d\n", sz);
// 	a[sz] = '\0';
// 	int close(int fd);
// }

/*Envía la string ’s’ al file descriptor dado, seguido de un salto de línea*/