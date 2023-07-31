/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:15:27 by vicrodri          #+#    #+#             */
/*   Updated: 2023/07/13 12:06:17 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_buffer(int fd, char *buffer)
{
	int		bread;
	char	*tmp;

	bread = 1;
	tmp = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	while (bread > 0)
	{
		bread = read(fd, tmp, BUFFER_SIZE);
		if (bread <= 0)
			break ;
		tmp[bread] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(tmp);
	if (bread < 0)
	{
		free (buffer);
		return (0);
	}
	return (buffer);
}

char	*ft_save_buffer(char *str)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free (str);
		return (0);
	}
	if (str[i] == '\n')
		i++;
	buffer = ft_calloc(sizeof(char), (ft_strlen(str) - i + 1));
	while (str[i] != '\0')
		buffer[j++] = str[i++];
	buffer[j] = 0;
	free(str);
	return (buffer);
}

char	*ft_fill_line(char *buffer)
{
	int		i;
	char	*result;

	i = 0;
	if (buffer[i] == '\0')
		return (0);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	result = (char *)ft_calloc(sizeof(char), i + 2);
	ft_memcpy(result, buffer, i);
	if (buffer[i] == '\n')
		result[i++] = '\n';
	result[i] = 0;
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = ft_read_buffer(fd, buffer);
	if (!buffer)
	{
		free(buffer);
		return (0);
	}
	result = ft_fill_line(buffer);
	buffer = ft_save_buffer(buffer);
	return (result);
}
