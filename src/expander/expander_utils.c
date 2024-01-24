/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:18:59 by erigolon          #+#    #+#             */
/*   Updated: 2024/01/24 19:28:18 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envlist	*get_env_var(char *str, t_minishell *ms)
{
	int			i;
	char		*word;
	char		*v_name;
	t_envlist	*env_variable;

	word = ft_strchr(str, '$');
	env_variable = 0;
	if (word)
	{
		i = 1;
		while (word[i] && word[i] != '\0' && \
			(ft_isalnum(word[i]) || word[i] == '_'))
			i++;
		v_name = ft_substr(word, 1, i - 1);
		env_variable = ft_getenv(v_name, ms->envlist);
		free(v_name);
	}
	return (env_variable);
}

char	*replace_str(char *og, char *find, char *repl)
{
	int		final_len;
	char	*str;
	int		i;
	int		j;

	final_len = ft_strlen(og) + ft_strlen(repl) - ft_strlen(find);
	str = ft_calloc(final_len + 1, sizeof(char));
	i = ft_strnstr(og, find, ft_strlen(og)) - og;
	j = -1;
	while (++j < i)
		str[j] = og[j];
	ft_strlcat(str, repl, final_len + 1);
	j = i + ft_strlen(repl);
	i += ft_strlen(find) - 1;
	while (og[i++] != '\0')
		str[j++] = og[i];
	free(og);
	free(find);
	return (str);
}

char	*get_dollar_name(char *str)
{
	char	*word;
	char	*v_name;
	int		i;

	v_name = NULL;
	word = ft_strchr(str, '$');
	if (word)
	{
		i = 1;
		while (word[i] && word[i] != '\0' && \
			(ft_isalnum(word[i]) || word[i] == '_' || word[i] == '?'))
			i++;
		if (i == 1)
			return (0);
		v_name = ft_substr(word, 0, i);
	}
	return (v_name);
}
