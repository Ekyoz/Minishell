/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:16:39 by atresall          #+#    #+#             */
/*   Updated: 2024/06/04 14:31:17 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pipe_end(char *command);
static char **split_quote_pipe(char *cmd);

char	**pipe_splitter(char *command)
{
	int		i;
	int		j;
	char	**pipe_splited;
	char *tmp;

	i = -1;
	j = -1;
	command = pipe_end(command);
	if (command == NULL)
		return NULL;
	add_history(command);
	add_file(command);
	pipe_splited = split_quote_pipe(command);
	while (pipe_splited[++i])
	{
		while (pipe_splited[i][++j] == ' ');
		tmp = pipe_splited[i];
		pipe_splited[i] = ft_substr(pipe_splited[i], j,
				ft_strlen(pipe_splited[i]) - j);
		free(tmp);
		j = -1;
	}
	if (i != pipe_counter(command))
		return (NULL);
	free(command);
	return (pipe_splited);
}

static char	*pipe_end(char *command)
{
	char	*input;
	size_t	i;

	i = ft_strlen(command);
	if (ft_strcmp(command, "|") == 0)
		return NULL;
	while (command[--i] == ' ')
		;
	command = ft_substr(command, 0, i + 1);
	if (command[ft_strlen(command) - 1] == '|')
	{
		input = readline("> ");
		command = ft_strjoin(command, input);
		command = pipe_end(command);
	}
	return (command);
}

static char **split_quote_pipe(char *cmd)
{
	int first_quote[2] = { 0, 0 };
	int last_quote[2] = {0 , 0};
	int last_line[2] = {-1, -1};
	char quote = '\0';
	char **arrays;

	arrays = string_to_array(cmd);

	if (ft_strchar(cmd, '|') == -1)
		return arrays;
	if (ft_strchar(cmd, '"') == -1 && ft_strchar(cmd, '\'') == -1)
		return ft_split(cmd, '|');
	else
	{
		get_first_quote(arrays, first_quote, &quote, last_line);
		get_last_quote(arrays, last_quote, &quote, last_line);
		if (quote == '\0')
		{
			return ft_split(cmd, '|');
		}
		else
		{
			if (first_quote[1] < ft_strchar(cmd, '|') && last_quote[1] > ft_strchar(cmd, '|'))
				return arrays;
			else
				return ft_split(cmd, '|');
		}
	}
}