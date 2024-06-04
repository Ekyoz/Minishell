/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:16:39 by atresall          #+#    #+#             */
/*   Updated: 2024/06/04 18:26:43 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pipe_end(char *command);

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
	// add_file(command);
	pipe_splited = ft_split(command, '|');
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
