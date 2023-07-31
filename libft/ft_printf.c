/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:29:15 by vicrodri          #+#    #+#             */
/*   Updated: 2023/06/20 15:49:35 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

char	*ft_toupper_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

void	ft_putchar(int c, int *total)
{
	write(1, &c, 1);
	*total = *total + 1;
}

void	ft_putstr(char *str, int *total)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i] != '\0')
	{
		ft_putchar(str[i], total);
		i++;
	}
}

void	vartype(char *a, char c, int *total, va_list ap)
{
	if (c == '%')
		ft_putchar('%', total);
	else if (c == 'c')
		ft_putchar(va_arg(ap, int), total);
	else if (c == 's')
		ft_putstr(va_arg(ap, char *), total);
	else if ((c == 'd' || c == 'i'))
		a = ft_itoa_c(va_arg(ap, int));
	else if (c == 'u')
		a = ft_itoa_uc(va_arg(ap, int));
	else if (c == 'p')
	{
		ft_putstr("0x", total);
		a = ft_itoa_hexa(va_arg(ap, unsigned long));
	}
	else if (c == 'x')
		a = ft_itoa_hexa(va_arg(ap, unsigned int));
	else if (c == 'X')
		a = ft_toupper_str(ft_itoa_hexa(va_arg(ap, unsigned int)));
	if (c == 'd' || c == 'i' || c == 'u' || c == 'p' || c == 'x' || c == 'X')
		ft_putstr(a, total);
	free(a);
}

int	ft_printf(char const *str, ...)
{
	va_list	ap;
	int		i;
	int		total;
	char	*a;

	a = 0;
	i = 0;
	total = 0;
	if (write(1, "", 0) == -1)
		return (-1);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] != '%')
			ft_putchar(str[i], &total);
		else if (str[i] == '%')
		{
			i++;
			vartype(a, str[i], &total, ap);
		}
		i++;
	}
	va_end(ap);
	return (total);
}

// int	main(void)
// {
// 	char *c = "hola";
// 	printf("un solo carácter: %c %c\n", 'a', 'b');
// 	ft_printf("un solo carácter: %c %c\n", 'a', 'b');
// 	printf("una string: %s\n", NULL);
// 	ft_printf("una string: %s\n", NULL);
// 	printf("puntero void *: %p\n", "");
// 	ft_printf("puntero void *: %p\n", "");
// 	printf("un número decimal (base 10): %d \n", -99);
// 	ft_printf("un número decimal (base 10): %d \n", -99);
// 	printf("un entero en base 10.: %i\n", 453);
// 	ft_printf("un entero en base 10.: %i\n", 453);
// 	printf("un número decimal (base 10) sin signo: %u\n", -453);
// 	ft_printf("un número decimal (base 10) sin signo: %u\n", -453);
// 	printf("%%c \n");
// 	ft_printf("%%c \n");
// 	printf("un número hexadecimal (base 16) en minúsculas: %x\n", -453);
// 	ft_printf("un número hexadecimal (base 16) en minúsculas: %x\n", -453);
// 	printf("un número hexadecimal (base 16) en mayúsculas: %X\n", 453);
// 	ft_printf("un número hexadecimal (base 16) en mayúsculas: %X\n", 453);
// }