/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:32:08 by vicrodri          #+#    #+#             */
/*   Updated: 2023/10/12 09:24:20 by erigolon         ###   ########.fr       */
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

void	ft_expander(char *input, t_minishell *ms)
{
	int	i;
	int	j;
	int k;
	char *tmp;

	i = 0;
	j = 0;
	while (ms->line[i])
	{
		if (ms->line[i] == '\'' && j != 1)
			j = 2;
		else if (ms->line[i] == '\"' && j == 0)
			j = 1;
		if (ms->line[i] == '$' && j != 2)
		{
			k = 0;
			while (ms->envp[k])
			{
				if (ft_strncmp(ms->envp[k], &ms->line[i + 1],
						ft_strlenenv(ms->envp[k])) == 0
					&& (ms->line[i + 1 + ft_strlenenv(ms->envp[k])] == ' '
						|| ms->line[i + 1 + ft_strlenenv(ms->envp[k])] == '\0'
						|| ms->line[i + 1 + ft_strlenenv(ms->envp[k])] == '\"' || ms->line[i + 1 + ft_strlenenv(ms->envp[k])] == '\''))
				{
					tmp = ft_strdup(&ms->line[i + 1 + ft_strlenenv(ms->envp[k])]);
					ft_memmove(&ms->line[i], &ms->envp[k][ft_strlenenv(ms->envp[k]) + 1],
						ft_strlen(ms->envp[k]) - ft_strlenenv(ms->envp[k]));
					ft_strlcat(ms->line, tmp, ft_strlen(ms->line) + ft_strlen(tmp) + 1);
					free(tmp);
					i = 0;
					j = 0;
				}

				k++;
			}
		}
		if (ms->line[i] == '$')
		{
			
		}
		i++;
	}
}

// void	ft_expander_double(t_minishell minishell)
// {
// 	int	i;
// 	int	j;
// 	int k;
	
// 	i = 0;
// 	while (minishell.input[i])
// 	{
// 		j = 0;
// 		while (minishell.input[i][j])
// 		{
// 			if (minishell.input[i][j] == '$'
// 				&& minishell.input[i][j - 1] != '\'')
// 			{
// 				k = 0;
// 				while (minishell.envp[k])
// 				{
// 					if (ft_strncmp(minishell.envp[k], &minishell.input[i][j + 1],
// 						ft_strlenenv(minishell.envp[k])) == 0)
// 						ft_memmove(&minishell.input[i][j],
// 							&minishell.envp[k][ft_strlenenv(minishell.envp[k]) + 1],
// 							ft_strlen(minishell.envp[k]) - 
// 							ft_strlenenv(minishell.envp[k]) + 1);
// 					k++;
// 				}
// 			}
// 		j++;
// 	}
// 		i++;
// 	}
// }


void	ft_lexer(char *input, t_minishell *minishell)
{
	ft_parser(minishell);
	// printf("path: %s\n", minishell->cmds->path);
	// printf("%d\n", minishell->cmds->i_fd_in);
	// printf("%d\n", minishell->cmds->i_fd_out);
	// printf("cmd: %s\n", minishell->cmds->cmd[0]);
	// printf("cmd: %s\n", minishell->cmds->cmd[1]);
	// printf("cmd: %s\n", minishell->cmds->cmd[2]);
	// printf("path: %s\n", minishell->cmds->next->path);
	// 	printf("%d\n", minishell->cmds->next->i_fd_in);
	// printf("%d\n", minishell->cmds->next->i_fd_out);
	// printf("cmd: %s\n", minishell->cmds->next->cmd[0]);
	// printf("cmd: %s\n", minishell->cmds->next->cmd[1]);
	// printf("cmd: %s\n", minishell->cmds->next->cmd[2]);
	// 	printf("path: %s\n", minishell->cmds->next->next->path);
	// printf("cmd: %s\n", minishell->cmds->next->next->cmd[0]);
	// printf("cmd: %s\n", minishell->cmds->next->next->cmd[1]);
	// printf("cmd: %s\n", minishell->cmds->next->next->cmd[2]);

}
