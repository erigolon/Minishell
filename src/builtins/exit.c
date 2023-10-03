/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:29:00 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/03 15:58:20 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_minishell *ms, char **nb)
{
	ft_putstr_fd("exit\n", 2);
	if (nb && nb[0])
	{
		if (check_exit(nb[0]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required", 2);
			ms->exit_status = 255;
		}
		else if (nb[1])
		{
			ft_putstr_fd("minishell: exit: too many arguments", 2);
			ms->exit_status = 1;
		}
	}
	ms->exit = 0;
}
/*
void	exit_test(t_minishell *ms)
{
	char *args1[] = {"123", NULL};
    char *args2[] = {"abc", NULL};
    char *args3[] = {"123", "456", NULL};

	printf("Caso 1 (exit con argumento numérico):\n");
    ft_exit(&ms, args1);
    printf("Exit Status: %d\n\n", ms.exit_status);

    ms.exit = 1;
    ms.exit_status = 0;

    printf("Caso 2 (exit con argumento no numérico):\n");
    ft_exit(&ms, args2);
    printf("Exit Status: %d\n\n", ms.exit_status);

    ms.exit = 1;
    ms.exit_status = 0;

    printf("Caso 3 (exit con demasiados argumentos):\n");
    ft_exit(&ms, args3);
    printf("Exit Status: %d\n\n", ms.exit_status);

}
*/