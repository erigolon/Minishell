/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_va.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:39:45 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/24 19:37:42 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_strjoin_free(char *s1, char *s2);
static char	*ft_check_args_to_join(va_list args, char c, char *join);


static char	*ft_fill_rest(char *str, int size);

int	ft_issign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

char	*ft_ftoa(double d)
{
	char	*str;
	char	*num;
	char	*rest;
	int		n;

	n = (int) d;
	num = ft_itoa(n);
	if (!num)
		return (NULL);
	d = d - (double) n;
	d = ft_power_double(d, 6);
	rest = ft_itoa(d);
	rest = ft_fill_rest(rest, 6);
	if (!rest)
	{
		free(num);
		return (NULL);
	}
	str = ft_strjoin_va("%s.%s", num, rest);
	free(num);
	free(rest);
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_fill_rest(char *str, int size)
{
	int		len;
	int		i;
	char	*tmp;

	len = ft_strlen(str);
	if (len < size)
	{
		tmp = ft_calloc(size + 1, sizeof(char));
		if (!tmp)
		{
			free(str);
			return (NULL);
		}
		i = -1;
		while (++i < size - len)
			tmp[i] = '0';
		while (i < size)
		{
			tmp[i] = str[i - (size - len)];
			i++;
		}
		free(str);
		return (tmp);
	}
	return (str);
}

char	*ft_chrjoin(char *s1, char c)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = ft_calloc(len + 2, sizeof(char));
	if (s2 == NULL)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(s2, s1, len + 1);
	s2[len] = c;
	s2[len + 1] = '\0';
	free(s1);
	return (s2);
}

char	*ft_strjoin_va(char const *s, ...)
{
	int		i;
	va_list	args;
	char	*join;

	i = 0;
	va_start(args, s);
	join = ft_calloc(sizeof(char), 1);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			join = ft_check_args_to_join(args, s[i], join);
		}
		else
			join = ft_chrjoin(join, s[i]);
		if (!join)
			break ;
		i++;
	}
	va_end(args);
	return (join);
}

static char	*ft_check_args_to_join(va_list args, char c, char *join)
{
	char	*str;

	if (c == 'i')
	{
		str = (ft_itoa(va_arg(args, int)));
		join = ft_strjoin_free(join, str);
	}
	if (c == 'f')
	{
		str = (ft_ftoa(va_arg(args, double)));
		join = ft_strjoin_free(join, str);
	}
	else if (c == 's')
	{
		str = ft_strdup(va_arg(args, char *));
		join = ft_strjoin_free(join, str);
	}
	return (join);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (s3);
}