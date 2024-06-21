/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:28:56 by atresall          #+#    #+#             */
/*   Updated: 2024/06/19 15:32:50 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_quoted(char **cmd, int first_quote[2], int last_quote[2]);
static char	**set_quote(char **cmd, t_env *env, int last_line[2],
				int *no_expandable);

char	**quote(char **cmd, t_env *env, int *no_expandable, int last_line[2])
{
	char	**temp_cmd;
	int		i;
	int		first_quote[2];
	int		last_quote[2];
	char	cquote;

	if (quoted(cmd) == -1)
		return (free_array(&cmd), free(no_expandable), NULL);
	if (quoted(cmd) == 0)
		return (expand_array(cmd, env, no_expandable));
	i = -1;
	temp_cmd = ft_arrdup(cmd);
	get_first_quote(cmd, first_quote, &cquote, last_line);
	get_last_quote(cmd, last_quote, &cquote, last_line);
	while (cmd[++i])
		if (i < first_quote[0] || i > last_quote[0])
			cmd[i] = expand_string(cmd[i], env);
	i = -1;
	while (++i < quote_strings(temp_cmd))
		cmd = set_quote(cmd, env, last_line, no_expandable);
	free_array(&temp_cmd);
	return (free(no_expandable), cmd);
}

static char	**set_quote(char **cmd, t_env *env, int last_line[2],
		int *no_expandable)
{
	int		first_quote[2];
	int		last_quote[2];
	char	c_quote;
	char	*c_quoted;
	char	*after;

	after = NULL;
	get_first_quote(cmd, first_quote, &c_quote, last_line);
	get_last_quote(cmd, last_quote, &c_quote, last_line);
	c_quoted = get_quoted(cmd, first_quote, last_quote);
	if (c_quote != '\'' && is_expandable(no_expandable, first_quote[0]))
		c_quoted = get_c_quoted(c_quoted, env);
	if (last_quote[1] < (int)ft_strlen(cmd[last_quote[0]]))
		after = ft_substr(cmd[last_quote[0]], last_quote[1] + 1,
				ft_strlen(cmd[last_quote[0]]) - 1);
	cmd = del_cmd(first_quote, last_quote, cmd);
	c_quoted = join_quote(c_quoted, get_before(first_quote, cmd), after, env);
	free(cmd[first_quote[0]]);
	cmd[first_quote[0]] = ft_strdup(c_quoted);
	last_line[0] = first_quote[0] - 1;
	last_line[1] = last_quote[1] - 2;
	return (free(c_quoted), cmd);
}

static char	*get_quoted(char **cmd, int first_quote[2], int last_quote[2])
{
	char	*quoted;
	int		i_cmd;
	int		len;
	char	*temp;

	i_cmd = -1;
	quoted = NULL;
	while (++i_cmd <= last_quote[0])
	{
		if (i_cmd == first_quote[0])
		{
			len = ft_strchar(&cmd[first_quote[0]][first_quote[1] + 1],
					cmd[first_quote[0]][first_quote[1]]);
			quoted = ft_substr(cmd[i_cmd], first_quote[1] + 1, len);
		}
		else if (i_cmd > first_quote[0] && i_cmd < last_quote[0])
		{
			temp = quoted;
			quoted = ft_strjoin(quoted, cmd[i_cmd]);
			free(temp);
		}
		else if (i_cmd == last_quote[0])
			get_quoted_join(cmd, &quoted, last_quote, i_cmd);
	}
	return (quoted);
}
