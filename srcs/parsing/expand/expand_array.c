/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:41:35 by atresall          #+#    #+#             */
/*   Updated: 2024/06/19 15:32:23 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_special_cases(char **cmd, int i_cmd);
static char	*extract_var(char *cmd, int *j_cmd);
static void	replace_var_cmd(char **cmd, int i_cmd, char *var, t_env *env);

char	**expand_array(char **cmd, t_env *env, int *no_expandable)
{
	int	i[3];

	i[0] = -1;
	i[1] = 0;
	while (cmd[++i[0]])
	{
		i[2] = -1;
		if (no_expandable[i[1]] && i[0] == no_expandable[i[1]])
		{
			i[1]++;
			continue ;
		}
		while (++i[2] < (int)ft_strlen(cmd[i[0]]))
		{
			if (handle_special_cases(cmd, i[0]) == 1)
				i[2] += ft_strchar(cmd[i[0]], '$') - 1;
			if (cmd[i[0]][i[2]] == '$' && cmd[i[0]][i[2] + 1] != '\0')
			{
				replace_var_cmd(cmd, i[0], extract_var(cmd[i[0]], &i[2]), env);
				if (cmd[i[0]] == NULL)
					ft_arrdel(cmd, i[0]);
			}
		}
	}
	return (free(no_expandable), cmd);
}

static int	handle_special_cases(char **cmd, int i_cmd)
{
	char	*temp;

	if (ft_strchar(cmd[i_cmd], '$') == -1)
		return (0);
	if (ft_strncmp(&cmd[i_cmd][ft_strchar(cmd[i_cmd], '$')], "$", 2) == 0)
		return (0);
	if (ft_strncmp(&cmd[i_cmd][ft_strchar(cmd[i_cmd], '$')], "$?", 2) == 0)
	{
		temp = ft_itoa(g_signal_status);
		cmd[i_cmd] = replace_env(temp, cmd[i_cmd], "$?");
		free(temp);
		return (1);
	}
	return (0);
}

static char	*extract_var(char *cmd, int *j_cmd)
{
	int		j;
	char	*substr;
	char	*var;
	char	*temp;

	j = *j_cmd;
	substr = ft_substr(cmd, j++, 1);
	var = ft_strjoin("", substr);
	free(substr);
	while (cmd[j] && cmd[j] != ' ' && cmd[j] != '\'' && cmd[j] != '$')
	{
		substr = ft_substr(cmd, j++, 1);
		temp = var;
		var = ft_strjoin(var, substr);
		free_chars(substr, temp, NULL, NULL);
	}
	*j_cmd = j - 1;
	return (var);
}

static void	replace_var_cmd(char **cmd, int i_cmd, char *var, t_env *env)
{
	char	*trimmed_var;
	char	*env_value;

	trimmed_var = ft_strtrim(var, "$");
	env_value = get_env_value(trimmed_var, env);
	cmd[i_cmd] = replace_env(env_value, cmd[i_cmd], var);
	free_chars(trimmed_var, var, env_value, NULL);
}
