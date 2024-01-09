/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:24:08 by erigolon          #+#    #+#             */
/*   Updated: 2023/09/27 12:12:12 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, 1024))
	{
		printf("%s\n", buffer);
		return (0);
	}
	else
		return (1);
}