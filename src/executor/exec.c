/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:18:50 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/24 19:34:46 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_child_redir_file(t_minishell *ms, t_cmdlist *tmp)
{
	if (tmp->fd_in)
	{
		if (tmp->fd_in < 0 && !tmp->append)
			ft_error_file(tmp->fd_in, ms);
		if (tmp->fd_in < 0 && tmp->append)
			exit(-1);
		ms->pipe[2 * ms->exe] = tmp->i_fd_in;
	}
	if (tmp->fd_out)
	{
		if (tmp->fd_out < 0)
			ft_error_file(tmp->fd_out, ms);
		ms->pipe[2 * ms->exe + 1] = tmp->i_fd_out;
	}
	else if (!tmp->next)
		ms->pipe[2 * ms->exe + 1] = tmp->i_fd_out;
	if (!ms->exe)
		ft_dup(tmp->i_fd_in, ms->pipe[2 * ms->exe + 1]);
	else
		ft_dup(ms->pipe[2 * ms->exe - 2], ms->pipe[2 * ms->exe + 1]);
}

static void	ft_childs_exe(t_minishell *ms, t_cmdlist *tmp)
{
	ft_close_pipe(ms);
	ft_accept_redirections(ms, tmp);
	close(ms->pipe[2 * ms->exe - 2]);
	ft_get_path(ms, tmp);
	if (!tmp->path)
		ft_error_exe(tmp->cmd, ": command not found\n", ms);
	ft_envlst_to_env(ms);
	execve(tmp->path, tmp->cmd, ms->envp);
	free_str(ms->envp, 0);
}

static int	ft_childs_pip(t_minishell *ms, t_cmdlist *tmp)
{
	pid_t	pros;
	int		status;

	status = ft_is_builtin(ms, tmp);
	if (status)
		return (ms->exit_status);
	signal(SIGINT, ft_sigint_proc);
	pros = fork();
	ms->child_pid = pros;
	signal(SIGQUIT, ft_sigint_proc);
	if (!pros)
	{
		ft_child_redir_file(ms, tmp);
		ft_childs_exe(ms, tmp);
		exit(-1);
	}
	waitpid(pros, &status, 0);
	if (status && ms->num_com > 1)
		return (127);
	if (status)
		return (1);
	return (0);
}

static void	ft_exec_init(t_minishell *ms)
{
	t_envlist	*tmp;

	tmp = ft_getenv("PATH", ms->explist);
	if (tmp)
		ms->path = ft_split(tmp->value, ':');
	else
		ms->path = NULL;
	ms->exe = 0;
}

void	exec(t_minishell *ms)
{
	t_cmdlist	*tmp;

	ft_exec_init(ms);
	tmp = ms->cmds;
	ms->pipe = ft_calloc(sizeof(int), ms->num_com * 2 + 1);
	while (ms->exe < ms->num_com)
	{
		pipe(ms->pipe + 2 * ms->exe);
		ms->exe += 1;
	}
	ms->exe = 0;
	while (tmp)
	{
		ms->exit_status = ft_childs_pip(ms, tmp);
		ms->exe += 1;
		tmp = tmp->next;
		wait(NULL);
		close(ms->pipe[2 * ms->exe - 2 + 1]);
	}
	ft_close_pipe(ms);
	free(ms->pipe);
	if (ms->path)
		free_str(ms->path, 0);
}
