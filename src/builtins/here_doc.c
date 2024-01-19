/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:14:57 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/17 21:15:36 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_read_here(char *limiter, int	*fd);

int	ft_here_doc(char *limiter)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	pid = fork();
	status = 0;
	signal(SIGINT, SIG_IGN);
	if (pid < 0)
		return (0);
	if (pid == 0)
		ft_read_here(limiter, fd);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
	}
	if (!status)
		return (fd[0]);
	return (-1);
}

static void	ft_read_here(char *limiter, int	*fd)
{
	int		size;
	char	*line;

	signal(SIGINT, ft_signheredoc);
	size = ft_strlen(limiter) + 1;
	while (42)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strncmp(line, limiter, size))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	exit(0);
}
