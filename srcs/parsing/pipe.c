/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:16:39 by atresall          #+#    #+#             */
/*   Updated: 2024/04/29 14:16:39 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_counter(const char *command)
{
	int i = -1;
	int pipe = 1;
	while (command[++i])
	{
		if (command[i] == '|')
			pipe++;
	}
	return pipe;
}

char *pipe_end(char *command)
{
	char *input;
	size_t i = ft_strlen(command);

	while (command[--i] == ' ');
	command = ft_substr(command, 0, i+1);
	if (command[ft_strlen(command) - 1] == '|')
	{
		input = readline("> ");
		command = ft_strjoin(command, input);
		command = pipe_end(command);
	}
	return command;
}

char **pipe_spliter(char *command)
{
	int i = -1;
	int j = -1;
	char **pipe_splited;

	command = pipe_end(command);
	add_history(command);

	pipe_splited = ft_split(command, '|');
	while (pipe_splited[++i])
	{
		while (pipe_splited[i][++j] == ' ');
		pipe_splited[i] = ft_substr(pipe_splited[i], j, ft_strlen(pipe_splited[i]) - j);
		j = -1;
	}
	if (i != pipe_counter(command))
		return NULL;
	return pipe_splited;
}