/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:42:58 by erigolon          #+#    #+#             */
/*   Updated: 2023/12/22 19:11:40 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*exec(t_minishell *ms)
{
	
	int	fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
	}
	else if(!pid)
	{
		if (ms->cmds->i_fd_in)
		{
			if (dup2(ms->cmds->i_fd_in, STDIN_FILENO) == -1)
				return (0);
			close(ms->cmds->i_fd_in);
		}
		if (ms->cmds->i_fd_out != STDOUT_FILENO)
		{
			if (dup2(ms->cmds->i_fd_out, STDOUT_FILENO) == -1)
				return (0);
			close(ms->cmds->i_fd_out);
		}
		else if (ms->cmds->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
			return (0);
		close(fd[WRITE_END]);
		close(fd[READ_END]);


		
		execve(ms->cmds->path,ms->cmds->cmd,ms->envp);
	}
	close(fd[WRITE_END]);
	if (ms->cmds->next && !(ms->cmds->next->i_fd_in))
		ms->cmds->next->i_fd_in = fd[READ_END];
	else
		close(fd[READ_END]);
	waitpid(-1, NULL, 0);
	return (0);
}

void exec2(t_minishell *ms)
{
	while(ms->cmds)
	{		
		exec(ms);
		ms->cmds = ms->cmds->next;
	}
}
