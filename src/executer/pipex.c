/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:05:00 by erigolon          #+#    #+#             */
/*   Updated: 2023/11/02 18:51:21 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*pipex_child(t_minishell *ms, int fd[2], t_cmdlist *temp)
{
	close(fd[0]);
	if (temp->next && dup2(fd[1], STDOUT_FILENO) == -1)
		return (0);
	if (!temp->next && dup2(temp->i_fd_out, STDOUT_FILENO) == -1)
		return (0);
	close(fd[1]);
	close(temp->i_fd_in);
	close(temp->i_fd_out);
	write(1, "pipex_child\n", 12);
	execve(temp->path, temp->cmd, ms->envp);
	return (0);
}

void	*pipex(t_minishell *ms)
{
	int				fd[2];
	t_cmdlist		*temp;
	
	temp = ms->cmds;
	if (dup2(temp->i_fd_in, STDIN_FILENO) == -1)
		return (0);
	close(temp->i_fd_in);
	while (temp)
	{
		if (pipe(fd) == -1)
			return (0);
		ms->child_pid = fork();
		if (ms->child_pid == -1)
			return (0);
		if (!ms->child_pid)
			pipex_child(ms, fd, temp);
		close(fd[1]);
		if (temp->next && dup2(fd[0], STDIN_FILENO) == -1)
			return (0);
		waitpid(ms->child_pid, NULL, 0);
		close(fd[0]);
		temp = temp->next;
	}
	return (NULL);
}
