/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:28:56 by atresall          #+#    #+#             */
/*   Updated: 2024/05/24 12:58:47 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_quoted(char **cmd, int first_quote[2], int last_quote[2]);
static char	**set_quote(char **cmd, t_env *env, int last_line[2]);
static int	quote_strings(char **tableau);

char	**quote(char **cmd, t_env *env)
{
	char	**temp_cmd;
	int		i;
	int		last_line[2];

	if (quoted(cmd) == false)
		return (expand_array(cmd, env));
	i = -1;
	temp_cmd = ft_arrdup(cmd);
	last_line[0] = -1;
	last_line[1] = -1;
	printf("Quote strings: %d\n", quote_strings(temp_cmd));
	while (cmd[++i])
		if (ft_strchar(cmd[i], '"') == -1 &&
			ft_strchar(cmd[i], '\'') == -1)
			cmd[i] = expand_string(cmd[i], env);
	i = -1;
	while (++i < quote_strings(temp_cmd))
		cmd = set_quote(cmd, env, last_line);
	return (cmd);
}

static char	**set_quote(char **cmd, t_env *env, int last_line[2])
{
	int		i;
	int		first_quote[2] = {0, 0};
	int		last_quote[2] = {0, 0};
	char	c_quote;
	char	*c_quoted;
	char	*after;
	char	*before;

	after = NULL;
	before = NULL;
	i = -1;
	get_first_quote(cmd, first_quote, &c_quote, last_line);
	get_last_quote(cmd, last_quote, &c_quote, last_line);

	c_quoted = get_quoted(cmd, first_quote, last_quote);
	if (c_quote != '\'')
		c_quoted = expand_string(c_quoted, env);

	if (first_quote[1] > 0)
		before = ft_substr(cmd[first_quote[0]], 0, first_quote[1]);
	if (last_quote[1] < (int)ft_strlen(cmd[last_quote[0]]))
		after = ft_substr(cmd[last_quote[0]], last_quote[1] + 1,
				ft_strlen(cmd[last_quote[0]])-1);

	i = last_quote[0];
	while ((i-1) >= first_quote[0])
		cmd = ft_arrdel(cmd, i--);

	if (before != NULL)
		c_quoted = ft_strjoin(expand_string(before, env), c_quoted);
	if (after != NULL)
		c_quoted = ft_strjoin(c_quoted, expand_string(after, env));
	cmd[first_quote[0]] = ft_strdup(c_quoted);
	printf("Before: %s\nAfter: %s\n", before, after);

	last_line[0] = first_quote[0]-1;
	last_line[1] = last_quote[1]-1;

	return (cmd);
}

static char	*get_quoted(char **cmd, int first_quote[2], int last_quote[2])
{
	char	*quoted;
	char	quote;
	int		i_cmd;
	int		len;

	i_cmd = -1;
	quoted = (char *)malloc(sizeof(char) * quote_len(cmd, first_quote,
				last_quote));
	quote = cmd[first_quote[0]][first_quote[1]];
	while (++i_cmd <= last_quote[0])
	{
		if (i_cmd == first_quote[0])
		{
			len = ft_strchar(&cmd[first_quote[0]][first_quote[1] + 1], quote);
			quoted = ft_substr(cmd[i_cmd], first_quote[1] + 1, len);
		}
		else if (i_cmd > first_quote[0] && i_cmd < last_quote[0])
			quoted = ft_strjoin(quoted, cmd[i_cmd]);
		else if (i_cmd == last_quote[0])
			quoted = ft_strjoin(quoted, ft_substr(cmd[i_cmd], 0,
						last_quote[1]));
	}
	return (quoted);
}

static int	quote_strings(char **tableau)
{
	int		len;
	int		s_quote;
	int		d_quote;
	char	*str;

	len = 0;
	s_quote = 0;
	d_quote = 0;
	while (*tableau)
	{
		str = *tableau;
		while (*str)
		{
			if (*str == '\'')
			{
				if (!d_quote)
				{
					if (s_quote)
					{
						s_quote = 0;
						len++;
					}
					else
						s_quote = 1;
				}
			}
			else if (*str == '\"')
			{
				if (!s_quote)
				{
					if (d_quote)
					{
						d_quote = 0;
						len++;
					}
					else
						d_quote = 1;
				}
			}
			str++;
		}
		tableau++;
	}
	return (len);
}
