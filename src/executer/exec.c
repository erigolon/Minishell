/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:42:58 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/10 17:31:39 by erigolon         ###   ########.fr       */
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
	if (ms->cmds->path)
	{
		// ms->cmds->path = "/bin/ls";
		// printf("Ejecutando: %s\n", ms->cmds->path);
		// printf("Argumentos: ");
		// for (int i = 0; ms->cmds->cmd[i] != NULL; ++i)
		//	printf("%s ", ms->cmds->cmd[i]);
		// printf("\n");
		// printf("Variables de entorno: ");
		// for (int i = 0; ms->envp[i] != NULL; ++i)
		// 	printf("%s ", ms->envp[i]);
		// printf("\n");
		if (execve(ms->cmds->path, ms->cmds->cmd, ms->envp) == -1)
		{
			perror("Error en execve");
			exit(1);
		}
	}
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
	int	i;

	i = 0;
	while (ms->cmds)
	{
		if (ft_strncmp(ms->cmds->cmd[0], "cd", 3) == 0
			|| ft_strncmp(ms->cmds->cmd[0], "echo", 5) == 0
			|| ft_strncmp(ms->cmds->cmd[0], "env", 4) == 0
			|| ft_strncmp(ms->cmds->cmd[0], "exit", 5) == 0
			|| ft_strncmp(ms->cmds->cmd[0], "export", 7) == 0
			|| ft_strncmp(ms->cmds->cmd[0], "pwd", 4) == 0
			|| ft_strncmp(ms->cmds->cmd[0], "unset", 6) == 0)
			ft_bt_select(ms->cmds, ms);
		else
			exec_cmd(ms);
		ms->cmds = ms->cmds->next;
		i++;
	}
	while (i > 0)
	{
		waitpid(-1, NULL, 0);
		i--;
	}
}
