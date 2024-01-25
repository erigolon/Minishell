/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:04 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/24 19:31:40 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*expand_tokens(t_lexer *lexer, t_minishell *ms)
{
	t_token		*tk;
	int			i;

	tk = lexer->token_list;
	i = 0;
	while (tk)
	{
		if (tk->status != SINGLE_QUOTE && tk->type != DELIMITER && \
			ft_strchr(tk->str, '$'))
		{
			while (tk->str[i] && tk->str[i] != '\0')
			{
				i += replace_next_dollar(&tk->str[i], ms, tk);
				if (i < 0)
					i = 0;
			}
			i = 0;
		}
		tk = tk->next;
	}
	return (lexer->token_list);
}

int	replace_next_dollar(char *str, t_minishell *ms, t_token *tok)
{
	char		*name;
	int			len;
	t_envlist	*env;

	name = get_dollar_name(str);
	if (!name)
		return (1);
	if (ft_strnstr(name, "$?", ft_strlen(name)))
		return (replace_exit_status(tok, ms, name));
	if (ft_isdigit(name[1]) || !ft_isalpha(name[1]))
		return (replace_dollar_digit(tok, ms, name));
	env = ft_getenv(&name[1], ms->envlist);
	len = ft_strlen(name);
	if (!env)
	{
		tok->str = replace_str(tok->str, name, "");
		if (tok->status == 3 && tok->str[0] == '\0')
			free_token(tok);
		return (-len);
	}
	tok->str = replace_str(tok->str, name, env->value);
	return (len);
}

int	replace_exit_status(t_token *tok, t_minishell *ms, char *free_str)
{
	char	*status;

	free(free_str);
	status = ft_itoa(ms->exit_status);
	tok->str = replace_str(tok->str, ft_strdup("$?"), status);
	free(status);
	return (1);
}

int	replace_dollar_digit(t_token *tok, t_minishell *ms, char *free_str)
{
	char		*str;
	t_envlist	*env;

	env = ft_getenv(&free_str[1], ms->envlist);
	if (env)
	{
		tok->str = replace_str(tok->str, free_str, env->value);
		return (1);
	}
	if (!ft_isdigit(free_str[1]))
	{
		free(free_str);
		return (1);
	}
	str = ft_substr(free_str, 0, 2);
	tok->str = replace_str(tok->str, str, "");
	free(free_str);
	return (-2);
}

void	ft_expander_directory(t_token *tok, t_minishell *m)
{
	t_envlist	*home;
	t_token		*tk;
	char		*s;

	tk = tok;
	while (tk)
	{
		if (tk->str && tk->str[0] == '~' && (tk->str[1] == '/' || \
			tk->str[1] == '\0') && tk->type == CHAR_TILDE)
		{
			home = ft_getenv("HOME", m->envlist);
			tk->type = EXPANDED;
			if (!home)
			{
				s = ft_strjoin("/Users/", ft_getenv("USER", m->envlist)->value);
				tk->str = replace_str(tk->str, ft_strdup("~"), s);
				free(s);
			}
			else
				tk->str = replace_str(tk->str, ft_strdup("~"), home->value);
		}
		else if (tk->str && ft_strchr(tk->str, '~'))
			tk->type = CHAR_NORMAL;
		tk = tk->next;
	}
}
