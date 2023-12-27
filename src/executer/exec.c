/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:42:58 by erigolon          #+#    #+#             */
/*   Updated: 2023/12/27 18:39:17 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*child_process(t_minishell *ms, int *fd)
{
	if (ms->cmds->i_fd_in != STDIN_FILENO)
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
	return (0);
}

void	exec_fork(t_minishell *ms, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
	}
	else if (!pid)
		child_process(ms, fd);
}

void	*exec_cmd(t_minishell *ms)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (0);
	exec_fork(ms, fd);
	close(fd[WRITE_END]);
	if (ms->cmds->next && !(ms->cmds->next->i_fd_in))
		ms->cmds->next->i_fd_in = fd[READ_END];
	else
		close(fd[READ_END]);
	if (ms->cmds->i_fd_in > 2)
		close (ms->cmds->i_fd_in);
	if (ms->cmds->i_fd_out > 2)
		close (ms->cmds->i_fd_out);
	return (0);
}

void	exec2(t_minishell *ms)
{
	while (ms->cmds)
	{
		if(ft_strncmp(ms->cmds->cmd[0], "cd", 3) == 0 || ft_strncmp(ms->cmds->cmd[0], "echo", 5) == 0 || ft_strncmp(ms->cmds->cmd[0], "env", 4) == 0 || ft_strncmp(ms->cmds->cmd[0], "exit", 5) == 0 || ft_strncmp(ms->cmds->cmd[0], "export", 7) == 0 || ft_strncmp(ms->cmds->cmd[0], "pwd", 4) == 0 || ft_strncmp(ms->cmds->cmd[0], "unset", 6) == 0)
			ft_bt_select(ms->cmds, ms);
		else
			exec_cmd(ms);
		ms->cmds = ms->cmds->next;
	}
	waitpid(-1, NULL, 0);
}
