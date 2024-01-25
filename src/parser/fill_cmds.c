/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:20 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/24 19:15:17 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tokens_to_commands(t_minishell *ms, t_lexer *lex)
{
	t_cmdlist	*cmd;
	t_token		*tok;
	int			n_cmds;

	if (!lex || !lex->token_list)
		return ;
	tok = lex->token_list;
	ms->cmds = ft_cmdlstnew();
	cmd = ms->cmds;
	n_cmds = 1;
	while (tok)
	{
		if (tok && tok->type == CHAR_PIPE && tok->next)
		{
			ft_cmdlstadd_back(&ms->cmds, ft_cmdlstnew());
			cmd = cmd->next;
			n_cmds++;
			tok = tok->next;
		}
		tok = fill_cmd(cmd, tok);
		open_files_cmd(cmd);
	}
	ms->lexer = lex;
	ms->num_com = n_cmds;
}

t_token	*fill_cmd(t_cmdlist *cmd, t_token *tok)
{
	if (tok->type == INFILE)
		cmd->fd_in = tok->str;
	if (tok->type == DELIMITER)
	{
		cmd->fd_in = tok->str;
		cmd->append = 1;
		cmd->i_fd_in = ft_here_doc(tok->str);
	}
	if (tok->type == OUTFILE)
		cmd->fd_out = tok->str;
	if (tok->type == OUTFILE_APPEND)
	{
		cmd->fd_out = tok->str;
		cmd->append = 1;
	}
	if ((tok->type == CHAR_NORMAL || tok->type == EXPANDED) && !cmd->cmd)
		get_all_args(cmd, tok);
	if (tok->next)
		return (tok->next);
	return (0);
}

void	get_all_args(t_cmdlist *cmd, t_token *tok)
{
	int	i;
	int	n_args;

	i = -1;
	n_args = count_args(tok);
	cmd->cmd = ft_calloc(n_args + 1, sizeof(char *));
	while (tok && tok->type != CHAR_PIPE)
	{
		if (tok->type == CHAR_NORMAL || tok->type == EXPANDED)
			cmd->cmd[++i] = ft_strdup(tok->str);
		tok = tok->next;
	}
	cmd->cmd[i + 1] = NULL;
}

int	count_args(t_token *tok)
{
	int	i;

	i = 0;
	while (tok && tok->type != CHAR_PIPE)
	{
		if (tok->type == CHAR_NORMAL || tok->type == EXPANDED)
			i++;
		tok = tok->next;
	}
	return (i);
}

int	open_files_cmd(t_cmdlist *cmd)
{
	if (cmd->fd_in && !cmd->append)
		cmd->i_fd_in = open(cmd->fd_in, O_RDONLY);
	if (cmd->fd_out && cmd->append)
		cmd->i_fd_out = open(cmd->fd_out, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (cmd->fd_out && !cmd->append)
		cmd->i_fd_out = open(cmd->fd_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->i_fd_in == -1 || cmd->i_fd_out == -1)
		return (-1);
	return (0);
}
