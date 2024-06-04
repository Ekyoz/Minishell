/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:11:44 by atresall          #+#    #+#             */
/*   Updated: 2024/06/04 18:41:31 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_key(char *line);
static char	*get_env_value(char *key, t_env *env);
static char	*replace_env(char *env, char *cmd, char *key);

char	**expand_array(char **cmd, t_env *env, int *no_expandable)
{
	int		i_cmd;
	int		j_cmd;
	int		i_exp;
	int		j;
	char	*var;
	char *sub;

	i_cmd = -1;
	i_exp = 0;
	var = NULL;
	while (cmd[++i_cmd])
	{
		j_cmd = -1;
		if (i_cmd == no_expandable[i_exp])
		{
			i_exp++;
			continue;
		}
		while (cmd[i_cmd][++j_cmd])
		{
			j = j_cmd;
			if (cmd[i_cmd][j_cmd] == '$')
			{
				while (cmd[i_cmd][j] && cmd[i_cmd][j] != ' '
					&& cmd[i_cmd][j] != '\'')
				{
					sub = ft_substr(cmd[i_cmd], j++, 1);
					var = ft_strcat(var, sub);
				}
				cmd[i_cmd] = replace_env(get_env_value(ft_strtrim(var, "$"),
							env), cmd[i_cmd], var);
				free(sub);
			}
		}
	}
	free(no_expandable);
	return (cmd);
}

char	*expand_string(char *cmd, t_env *env)
{
	int		i_cmd;
	int		j;
	char	*var;

	i_cmd = -1;
	var = NULL;
	while (cmd[++i_cmd])
	{
		j = i_cmd;
		if (cmd[i_cmd] == '$')
		{
			while (cmd[j] && cmd[j] != ' ' && cmd[j] != '\'' && cmd[j] != '"')
				var = ft_strcat(var, ft_substr(cmd, j++, 1));
			cmd = replace_env(get_env_value(ft_strtrim(var, "$"), env), cmd,
					var);
		}
	}
	return (cmd);
}

static char	*get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(get_env_key(env->value), key) == 0)
			return (ft_substr(env->value, ft_strchar(env->value, '=') + 1,ft_strlen(env->value)));
		env = env->next;
	}
	return ("");
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

static char	*replace_env(char *env, char *cmd, char *key)
{
	char	*replaced;
	char	*after;
	long	pos;

	if (ft_strnstr(cmd, key, ft_strlen(cmd)) != NULL)
	{
		pos = ft_strnstr(cmd, key, ft_strlen(cmd)) - cmd;
		replaced = ft_substr(cmd, 0, pos);
		replaced = ft_strjoin(replaced, env);
		after = ft_substr(cmd, pos + ft_strlen(key), ft_strlen(cmd) - (pos
					+ ft_strlen(key)));
		replaced = ft_strjoin(replaced, after);
		free(after);
		return (replaced);
	}
	return (NULL);
}
