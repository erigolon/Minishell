/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:46:54 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/04 17:25:07 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

t_cmdlist	*ft_cmdlstlast(t_cmdlist *lst)
{
	t_cmdlist	*result;

	if (!lst)
		return (0);
	result = lst;
	while (result->next != NULL)
	{
		result = result->next;
	}
	return (result);
}

void	ft_cmdlstadd_back(t_cmdlist **cmdlist, t_cmdlist *new)
{
	t_cmdlist	*temp;

	temp = ft_cmdlstlast(*cmdlist);
	if (temp)
		temp->next = new;
	else
		*cmdlist = new;
}

t_cmdlist	*ft_cmdlstnew(void *content)
{
	t_cmdlist	*result;

	result = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!result)
		return (NULL);
	result->cmd = NULL;
	result->path = NULL;
	result->fd_in = NULL;
	result->fd_out = NULL;
	result->i_fd_in = 0;
	result->i_fd_out = 0;
	result->next = NULL;
	return (result);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	paths = ft_calloc(ft_strlen(envp[i] + 5), sizeof(char));
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
	{
		write(2, "Error: PATH not found\n", 22);
		exit(1);
	}
	return (paths);
}

char	*ft_join(char *path, char *cmd)
{
	char	*tmp;
	char	*tmp2;
	char	**tmp3;

	tmp = ft_strjoin(path, "/");
	tmp3 = ft_split(cmd, ' ');
	tmp2 = ft_strjoin(tmp, tmp3[0]);
	// free_arrays(tmp3);
	free(tmp);
	return (tmp2);
}

void	ft_getcmd(t_minishell *minishell,t_cmdlist *cmds, char *cmdargs)
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
	int i;
	int j;
	int fd;

	i = 0;
	j = 0;

	t_cmdlist *current_cmd = ft_cmdlstnew(NULL);
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
			current_cmd->i_fd_out = open(minishell->input[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(current_cmd->i_fd_out, STDIN_FILENO);
		}
		else if (minishell->input[i][0] == '|')
		{
			ft_cmdlstadd_back(&current_cmd, ft_cmdlstnew(NULL));
			current_cmd = current_cmd->next;
			current_cmd->cmd = ft_calloc(ft_strlen(minishell->input[i]), sizeof(char));
			j = 0;
		}
		i++;
	}
}