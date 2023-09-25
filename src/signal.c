/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:59:31 by erigolon          #+#    #+#             */
/*   Updated: 2023/09/21 13:13:33 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

// Aquí se maneja tanto la señnal SIGQUIT como SIGINT
void	ft_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		signal(SIGINT, ft_handler);
	}
}
