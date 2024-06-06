/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:11:44 by atresall          #+#    #+#             */
/*   Updated: 2024/06/04 19:19:51 by bpoyet           ###   ########.fr       */
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
		if (no_expandable[i_exp] && i_cmd == no_expandable[i_exp])
		{
			i_exp++;
			continue;
		}
		while (j_cmd < (int)ft_strlen(cmd[i_cmd]) && cmd[i_cmd][++j_cmd])
		{
			j = j_cmd;
			if (ft_strcmp(cmd[i_cmd], "$") == 0)
				return cmd;
			if (ft_strcmp(cmd[i_cmd], "$?") == 0)
			{
				cmd[i_cmd] = replace_env(ft_itoa(signal_status), cmd[i_cmd], "$?");
				return cmd;
			}
			if (cmd[i_cmd][j_cmd] == '$')
			{
				char *substr = ft_substr(cmd[i_cmd], j++, 1);
				var = ft_strjoin("", substr);
				while (cmd[i_cmd][j] && cmd[i_cmd][j] != ' '
					&& cmd[i_cmd][j] != '\'' && cmd[i_cmd][j] != '$')
				{
					substr = ft_substr(cmd[i_cmd], j++, 1);
					var = ft_strjoin(var, substr);
					free(substr);
				}
				char *trimmed_var = ft_strtrim(var, "$");
				char *env_value = get_env_value(trimmed_var, env);
				if (ft_strcmp(env_value, "") == 0)
					j_cmd--;
  				cmd[i_cmd] = replace_env(env_value, cmd[i_cmd], var);
				var = NULL;
				free(trimmed_var);
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
	char *temp;

	i_cmd = -1;
	var = NULL;
	if (ft_strcmp(cmd, "$") == 0)
		return cmd;
	if (ft_strcmp(cmd, "$?") == 0)
		return replace_env(ft_itoa(signal_status), cmd, "$?");

	while (i_cmd < (int)ft_strlen(cmd) && cmd[++i_cmd])
	{
		j = i_cmd;
		if (cmd[i_cmd] == '$')
		{
			char *substr = ft_substr(cmd, j++, 1);
			var = ft_strjoin("", substr);
			while (cmd[j] && cmd[j] != ' ' && cmd[j] != '\'' && cmd[j] != '\"' && cmd[j] != '$')
			{
				substr = ft_substr(cmd, j++, 1);
				var = ft_strjoin(var, substr);
				free(substr);
			}
			char *trimmed_var = ft_strtrim(var, "$");
			char *env_value = get_env_value(trimmed_var, env);
			if (ft_strcmp(env_value, "") == 0)
				i_cmd--;
			cmd = replace_env(env_value, cmd, var);
			var = NULL;
			free(trimmed_var);
		}
	}
	free(var);
	return (cmd);
}

static char	*get_env_value(char *key, t_env *env)
{
	char *env_key;

	while (env)
	{
		env_key = get_env_key(env->value);
		if (ft_strcmp(env_key, key) == 0)
			return (free(env_key), ft_substr(env->value, ft_strchar(env->value, '=') + 1,ft_strlen(env->value)));
		env = env->next;
		free(env_key);
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
