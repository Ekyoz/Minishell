/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:11:44 by atresall          #+#    #+#             */
/*   Updated: 2024/05/29 12:20:09 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_key(char *line);
static char	*get_env_value(char *key, t_env *env);
static char	*replace_env(char *env, char *cmd, char *key);

char	**expand_array(char **cmd, t_env *env)
{
	int		i_cmd;
	int		j_cmd;
	int		j;
	char	*var;

	i_cmd = -1;
	var = NULL;
	while (cmd[++i_cmd])
	{
		j_cmd = -1;
		while (cmd[i_cmd][++j_cmd])
		{
			j = j_cmd;
			if (cmd[i_cmd][j_cmd] == '$')
			{
				while (cmd[i_cmd][j] && cmd[i_cmd][j] != ' '
					&& cmd[i_cmd][j] != '\'')
					var = ft_strcat(var, ft_substr(cmd[i_cmd], j++, 1));
				cmd[i_cmd] = replace_env(get_env_value(ft_strtrim(var, "$"),
							env), cmd[i_cmd], var);
				var = NULL;
			}
		}
	}
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
	int	len;
	int	len_space;
	int	len_quote;

	len_space = ft_strchar(key, ' ');
	len_quote = ft_strchar(key, '\'');
	if (len_space != -1 && len_space < len_quote)
		len = len_space;
	else if (len_quote != -1 && len_quote < len_space)
		len = len_quote;
	while (env)
	{
		if (ft_strcmp(get_env_key(env->value), key) == 0)
			return (ft_substr(env->value, ft_strchar(env->value, '=') + 1,
					len));
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
