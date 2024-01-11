/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:27:37 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/11 13:27:05 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_cmdlist(t_cmdlist *cmdlist)
{
	t_cmdlist	*temp;

	write(1, "tercero", 7); //
	while (cmdlist != NULL)
	{
		printf("freeing cmd: %s\n", cmdlist->cmd[0]);
		temp = cmdlist->next;
		free(cmdlist->path);
		// printf("freeing cmd: %s\n", cmdlist->cmd[0]);
		// free_str(cmdlist->cmd, 0);
		free(cmdlist);
		cmdlist = temp;
	}
}
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

t_cmdlist	*ft_cmdlstnew(void)
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
	// free_str(tmp3, 0);
	free(tmp);
	return (tmp2);
}