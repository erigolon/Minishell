/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:26:30 by erigolon          #+#    #+#             */
/*   Updated: 2023/09/26 11:22:15 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envlist	*split_n_fill_env(t_envlist	*new_env, char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (new_env->env)
		free(new_env->env);
	new_env->env = ft_calloc(sizeof(char), i + 2);
	ft_strlcpy(new_env->env, env, i + 1);
	if (new_env->value)
		free(new_env->value);
	if (env[i] == '=')
		new_env->value = ft_strdup(&env[i + 1]);
	else
		new_env->value = NULL;
	return (new_env);
}
