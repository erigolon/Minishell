/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:32:08 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/26 20:45:15 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

size_t	ft_strlenenv(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=')
		i++;
	return (i);
}

void	ft_expander(t_minishell *ms)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*tmp;

	i = 0;
	while (ms->input[i] != NULL)
	{
		j = 0;
		l = 0;
		while (ms->input[i][j] != '\0')
		{
			if (ms->input[i][j] == '\'' && l != 1)
				l = 2;
			else if (ms->input[i][j] == '\"' && l == 0)
				l = 1;
			if (ms->input[i][j] == '$' && l != 2)
			{
				k = 0;
				while (ms->envp[k])
				{
					if (ft_strncmp(ms->envp[k], &ms->input[i][j + 1],
						ft_strlenenv(ms->envp[k])) == 0
						&& (ms->input[i][j + 1
							+ ft_strlenenv(ms->envp[k])] == ' '
							|| ms->input[i][j + 1
							+ ft_strlenenv(ms->envp[k])] == '\0'
							|| ms->input[i][j + 1
							+ ft_strlenenv(ms->envp[k])] == '\"'
							|| ms->input[i][j + 1
							+ ft_strlenenv(ms->envp[k])] == '\''))
					{
						if (l == 1)
								tmp = ft_strdup(&ms->input[i][j
									+ 1 + ft_strlenenv(ms->envp[k])]);
						ft_bzero(&ms->input[i][j], ft_strlen(&ms->input[i][j]));
						ms->input[i] = ft_strjoinizq(ms->input[i],
								&ms->envp[k][ft_strlenenv(ms->envp[k]) + 1]);
						if (l == 1)
						{
							ms->input[i] = ft_strjoinizq(ms->input[i], tmp);
							free(tmp);
						}
						l = 0;
					}
					k++;
				}
			}
			if (ms->input[i][j] == '$' && l != 2)
			{
				ft_bzero(ms->input[i], ft_strlen(ms->input[i]));
			}
			j++;
		}
		i++;
	}	
}

void	ft_expander_directory(t_minishell *ms)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	while (ms->input[i] != NULL)
	{
		j = 0;
		while (ms->input[i][j] != '\0')
		{
			if (ms->input[i][j] == '~' && ms->input[i][j + 1] == '/')
			{
				k = 0;
				while (ms->envp[k])
				{
					if (ft_strncmp(ms->envp[k], "HOME=", 5) == 0)
					{
						tmp = ft_strdup(&ms->input[i][j + 1]);
						free(ms->input[i]);
						tmp = ft_strjoinder(&ms->envp[k][5], tmp);
						ms->input[i] = ft_strdup(tmp);
						free(tmp);
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
}

void	ft_quotestrim(t_minishell *ms)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	tmp;

	i = 0;
	while (ms->input[i] != NULL)
	{
		j = 0;
		k = 0;
		while (ms->input[i][j] != '\0')
		{
			if (ms->input[i][j] == '\"' || ms->input[i][j] == '\'')
			{
				k++;
			}
			j++;
		}
		if (k % 2 != 0)
		{
			printf("Error: quote\n");
			return ;
		}
		k = 0;
		j = 0;
		while (ms->input[i][j] != '\0')
		{
			if (ms->input[i][j] == '\"' || ms->input[i][j] == '\'')
			{
				tmp = ms->input[i][j];
				l = j;
				while (ms->input[i][l] != '\0')
				{
					ms->input[i][l] = ms->input[i][l + 1];
					l++;
				}
				j++;
				while (ms->input[i][j] != tmp)
				{
					j++;
				}
				l = j;
				while (ms->input[i][l] != '\0')
				{
					ms->input[i][l] = ms->input[i][l + 1];
					l++;
				}
			}
			j++;
		}
		i++;
	}
}

void	ft_lexer(t_minishell *minishell)
{
	printf("path: %s\n", minishell->cmds->path);
	printf("%d\n", minishell->cmds->i_fd_in);
	printf("%d\n", minishell->cmds->i_fd_out);
	printf("cmd: %s\n", minishell->cmds->cmd[0]);
	printf("cmd: %s\n", minishell->cmds->cmd[1]);
	printf("path: %s\n", minishell->cmds->next->path);
		printf("%d\n", minishell->cmds->next->i_fd_in);
	printf("%d\n", minishell->cmds->next->i_fd_out);
	printf("cmd: %s\n", minishell->cmds->next->cmd[0]);
	printf("cmd: %s\n", minishell->cmds->next->cmd[1]);
	printf("cmd: %s\n", minishell->cmds->next->cmd[2]);
		printf("path: %s\n", minishell->cmds->next->next->path);
	printf("cmd: %s\n", minishell->cmds->next->next->cmd[0]);
	printf("cmd: %s\n", minishell->cmds->next->next->cmd[1]);
	printf("cmd: %s\n", minishell->cmds->next->next->cmd[2]);
}
