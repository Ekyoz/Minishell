/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:56:53 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/04 13:30:37 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_first_quote(char **cmd, int pos[2], char *c_quote, int last_line[2])
{
	int	i;
	int	j;

	i = last_line[0];
	j = last_line[1];
	while (cmd[++i])
	{
		while (cmd[i][++j])
		{
			if (cmd[i][j] == '\'' || cmd[i][j] == '"')
			{
				pos[0] = i;
				pos[1] = j;
				*c_quote = cmd[i][j];
				return ;
			}
		}
		j = -1;
	}
}

void	get_last_quote(char **cmd, int pos[2], char *c_quote, int last_line[2])
{
	int	i;
	int	j;
	int	first_quote[2];

	i = -1;
	get_first_quote(cmd, first_quote, c_quote, last_line);
	i = first_quote[0] - 1;
	j = first_quote[1] - 1;
	while (cmd[++i])
	{
		while (cmd[i][++j])
		{
			if (cmd[i][j] == *c_quote)
			{
				if (i == first_quote[0] && j == first_quote[1])
					continue ;
				pos[0] = i;
				pos[1] = j;
				*c_quote = cmd[i][j];
				return ;
			}
		}
		j = -1;
	}
}

char	*join_quote(char *c_quoted, char *before, char *after, t_env *env)
{
	char	*temp;

	if (before != NULL)
	{
		temp = c_quoted;
		c_quoted = ft_strjoin(expand_string(before, env), temp);
		free(temp);
		temp = NULL;
	}
	if (after != NULL)
	{
		temp = c_quoted;
		c_quoted = ft_strjoin(c_quoted, expand_string(after, env));
		free(temp);
		temp = NULL;
	}
	free_chars(after, before, NULL, NULL);
	return (c_quoted);
}

char	*get_before(int first_quote[2], char **cmd)
{
	if (first_quote[1] > 0)
		return (ft_substr(cmd[first_quote[0]], 0, first_quote[1]));
	return (NULL);
}

char	*get_c_quoted(char *c_quoted, t_env *env)
{
	char	*temp;

	temp = expand_string(c_quoted, env);
	c_quoted = ft_strdup(temp);
	free(temp);
	return (c_quoted);
}
