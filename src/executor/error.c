/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:14:46 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/17 21:56:12 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error_exe(char **arg, char *msg, t_minishell *ms)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(msg, 2);
	ft_free_fork(ms);
	exit(-1);
}

void	ft_error_file(char *file, t_minishell *ms)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	if (access(file, F_OK))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Permission denied\n", 2);
	ft_free_fork(ms);
	exit(-1);
}
