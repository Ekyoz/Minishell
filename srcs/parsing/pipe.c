/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:16:39 by atresall          #+#    #+#             */
/*   Updated: 2024/06/10 14:41:30 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pipe_end(char *command);
static char	**split_quote_pipe(char *cmd);

char	**pipe_splitter(char *command)
{
	int		i;
	int		j;
	char	**pipe_splited;
	char	*tmp;

	i = -1;
	j = -1;
	command = pipe_end(command);
	if (command == NULL)
		return (NULL);
	if (ft_strchar(command, '|') == -1)
		return (string_to_array(command));
	pipe_splited = split_quote_pipe(command);
	while (pipe_splited[++i])
	{
		while (pipe_splited[i][++j] == ' ')
			;
		tmp = pipe_splited[i];
		pipe_splited[i] = ft_substr(tmp, j, ft_strlen(pipe_splited[i]) - j);
		free(tmp);
		j = -1;
	}
	if (i != pipe_counter(command))
		return (free_array(&pipe_splited), free(command), NULL);
	return (free(command), pipe_splited);
}

static char	*pipe_end(char *command)
{
	char	*temp;
	int		i;

	if (command == NULL || ft_strcmp(command, "|") == 0)
		return (NULL);
	add_history(command);
	if (ft_strchar(command, '|') == -1)
		return (command);
	i = (int)ft_strlen(command);
	while (command[--i] == ' ')
		;
	temp = command;
	command = ft_substr(temp, 0, i + 1);
	if (command[ft_strlen(command) - 1] == '|')
	{
		ft_putstr_fd("Minihell: Pipe error\n", 2);
		free(command);
		return (NULL);
	}
	return (command);
}

static char	init_quote(char **arrays, int *first_quote, int *last_quote)
{
	int		last_line[2];
	char	c_quote;

	c_quote = '\0';
	last_line[0] = -1;
	last_line[1] = -1;
	get_first_quote(arrays, first_quote, &c_quote, last_line);
	get_last_quote(arrays, last_quote, &c_quote, last_line);
	return (c_quote);
}

static char	**split_quote_pipe(char *cmd)
{
	int		first_quote[2];
	int		last_quote[2];
	char	quote;
	char	**arrays;

	arrays = string_to_array(cmd);
	if (ft_strchar(cmd, '|') == -1)
		return (arrays);
	if (ft_strchar(cmd, '"') == -1 && ft_strchar(cmd, '\'') == -1)
		return (free_array(&arrays), ft_split(cmd, '|'));
	else
	{
		quote = init_quote(arrays, first_quote, last_quote);
		if (quote == '\0')
			return (free_array(&arrays), ft_split(cmd, '|'));
		else
		{
			if (first_quote[1] < ft_strchar(cmd, '|')
				&& last_quote[1] > ft_strchar(cmd, '|'))
				return (arrays);
			else
				return (free_array(&arrays), ft_split(cmd, '|'));
		}
	}
}
