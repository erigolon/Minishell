/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:46:54 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/18 17:27:28 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	ft_getcmd(t_minishell *minishell, t_cmdlist *cmds, char *cmdargs)
{
	int		i;
	char	**paths;

	paths = get_paths(minishell->envp);
	i = -1;
	while (paths[++i])
	{
		if (cmdargs[0] == '/' || cmdargs[0] == '.')
			cmds->path = ft_strdup(cmdargs);
		else
			cmds->path = ft_join(paths[i], cmdargs);
		if (access(cmds->path, X_OK) == 0)
		{
			break ;
		}
		else
		{
			free(cmds->path);
			cmds->path = NULL;
		}
	}
}

void	ft_path(t_minishell *minishell, char *input, t_cmdlist *cmds)
{
	char	*builtin[7];
	int		i;

	i = 0;
	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	if (input[0] != '|' && input[0] != '<' && input[0] != '>')
	{
		ft_getcmd(minishell, cmds, input);
	}
	while (i < 7)
	{
		if (ft_strncmp(input, builtin[i], ft_strlen(builtin[i])) == 0)
		{
			cmds->path = NULL;
			break ;
		}
		i++;
	}
}

void	ft_parser(t_minishell *minishell)
{
	int			i;
	int			j;
	int			fd;
	t_cmdlist	*current_cmd;

	i = 0;
	j = 0;
	current_cmd = ft_cmdlstnew(NULL);
	current_cmd->cmd = ft_calloc(ft_strlen(minishell->input[i]), sizeof(char));
	minishell->cmds = current_cmd;
	while (minishell->input[i])
	{
		if (minishell->input[i][0] != '<' && minishell->input[i][0] != '>'
			&& minishell->input[i][0] != '|')
		{
			if (current_cmd->path == NULL)
				ft_path(minishell, minishell->input[i], current_cmd);
			current_cmd->cmd[j] = ft_strdup(minishell->input[i]);
			j++;
		}
		else if (minishell->input[i][0] == '<')
		{
			current_cmd->i_fd_in = open(minishell->input[i + 1], O_RDONLY);
			dup2(current_cmd->i_fd_out, STDOUT_FILENO);
		}
		else if (minishell->input[i][0] == '>')
		{
			current_cmd->i_fd_out = open(minishell->input[i + 1],
					O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(current_cmd->i_fd_out, STDIN_FILENO);
		}
		else if (minishell->input[i][0] == '|')
		{
			ft_cmdlstadd_back(&current_cmd, ft_cmdlstnew(NULL));
			current_cmd = current_cmd->next;
			current_cmd->cmd = ft_calloc(ft_strlen(minishell->input[i]),
					sizeof(char));
			j = 0;
		}
		i++;
	}
}