/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:03:19 by atresall          #+#    #+#             */
/*   Updated: 2024/06/11 19:03:19 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_special_tokens(char **cmd);
static char	*extract_var(char *cmd, int *i_cmd);
static void	replace_var_in_cmd(char **cmd, char *var, t_env *env, int *i_cmd);

char	*expand_string(char *cmd, t_env *env)
{
	int		i_cmd;
	char	*var;

	i_cmd = -1;
	while (i_cmd < (int)ft_strlen(cmd) && cmd[++i_cmd])
	{
		if (handle_special_tokens(&cmd) == 1)
		{
			i_cmd += ft_strchar(cmd, '$') - 1;
			continue ;
		}
		if (cmd[i_cmd] == '$' && cmd[i_cmd + 1] != '\0')
		{
			var = extract_var(cmd, &i_cmd);
			replace_var_in_cmd(&cmd, var, env, &i_cmd);
		}
	}
	return (cmd);
}

static int	handle_special_tokens(char **cmd)
{
	if (ft_strchar(*cmd, '$') == -1)
		return (0);
	if (ft_strncmp(&cmd[0][ft_strchar(*cmd, '$')], "$ ", 2) == 0)
		return (1);
	if (ft_strncmp(&cmd[0][ft_strchar(*cmd, '$')], "$?", 2) == 0)
	{
		*cmd = replace_env(ft_itoa(g_signal_status), *cmd, "$?");
		return (1);
	}
	return (0);
}

static char	*extract_var(char *cmd, int *i_cmd)
{
	int		j;
	char	*substr;
	char	*var;
	char	*temp;

	j = *i_cmd;
	substr = ft_substr(cmd, j++, 1);
	var = ft_strjoin("", substr);
	free(substr);
	while (cmd[j] && cmd[j] != ' ' && cmd[j] != '\'' && cmd[j] != '\"'
		&& cmd[j] != '$')
	{
		substr = ft_substr(cmd, j++, 1);
		temp = var;
		var = ft_strjoin(var, substr);
		free_chars(substr, temp, NULL, NULL);
	}
	*i_cmd = j - 1;
	return (var);
}

static void	replace_var_in_cmd(char **cmd, char *var, t_env *env, int *i_cmd)
{
	char	*trimmed_var;
	char	*env_value;

	trimmed_var = ft_strtrim(var, "$");
	env_value = get_env_value(trimmed_var, env);
	if (ft_strcmp(env_value, "") == 0)
		(*i_cmd)--;
	*cmd = replace_env(env_value, *cmd, var);
	free_chars(trimmed_var, var, env_value, NULL);
}
