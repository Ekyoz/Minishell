/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:11:44 by atresall          #+#    #+#             */
/*   Updated: 2024/06/18 15:48:43 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_key(char *line);

char	*get_env_value(char *key, t_env *env)
{
	char	*env_key;

	while (env)
	{
		env_key = get_env_key(env->value);
		if (ft_strcmp(env_key, key) == 0)
			return (free(env_key), ft_substr(env->value, ft_strchar(env->value,
						'=') + 1, ft_strlen(env->value)));
		env = env->next;
		free(env_key);
	}
	return (ft_strdup(" "));
}

char	*replace_env(char *env, char *cmd, char *key)
{
	char	*replaced;
	char	*after;
	char	*temp;
	long	pos;

	if (ft_strnstr(cmd, key, ft_strlen(cmd)) != NULL)
	{
		pos = ft_strnstr(cmd, key, ft_strlen(cmd)) - cmd;
		replaced = ft_substr(cmd, 0, pos);
		temp = replaced;
		replaced = ft_strjoin(replaced, env);
		after = ft_substr(cmd, pos + ft_strlen(key), ft_strlen(cmd) - (pos
					+ ft_strlen(key)));
		free(temp);
		temp = replaced;
		replaced = ft_strjoin(replaced, after);
		free_chars(after, temp, cmd, NULL);
		return (replaced);
	}
	return (free(cmd), NULL);
}

static char	*get_env_key(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == '=')
			return (ft_substr(line, 0, i));
	return (line);
}
