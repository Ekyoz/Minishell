/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:05:17 by atresall          #+#    #+#             */
/*   Updated: 2024/04/29 16:09:22 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int split_count(char *command) {
	int i = 0;
	int count = 0;
	bool in_word = false;

	while (command[i])
	{
		if (is_token(command, i) || command[i] == ' ')
		{
			if (in_word)
			{
				count++;
				in_word = false;
			}
			if (is_token(command, i))
			{
				count++;
				if (command[i] == '>' || command[i] == '<')
					i++;
			}
		}
		else
			if (!in_word)
				in_word = true;
		i++;
	}
	if (in_word)
		count++;
	return count;
}

char **check_redir(char *command) //ls -e>output
{
	int index_space = -1;
	int index_token = 0;
	int index_command = 0;
	int redir_out;
	char **space_split;
	char **token_split;
	char **command_split = (char**) malloc(sizeof(char*) * split_count(command));

	space_split = ft_split(command, ' '); // "ls", "-e>output"

	while (space_split[++index_space])
	{
		redir_out = ft_strchar(space_split[index_space], '>');

		if (redir_out == -1) // il n'y a pas de '>'
			command_split[index_command++] = space_split[index_space];
		else if (redir_out == 0 || redir_out == (int)ft_strlen(space_split[index_space]) - 1) //si le > est en premier ou dernier
		{
			if (split_count(space_split[index_space]) > 1) //si il est pas vide ">out"
			{
				token_split = ft_split_sep(space_split[index_space], '>');
//				for (int j = 0; j < split_count(space_split[index_space]); ++j) {
//					printf("token: %s\n", token_split[j]);
//				}
				while (token_split[index_token])				// je mets chaque element de split token dans la commande general
					command_split[index_command++] = token_split[index_token++];
				free(token_split);
			}
			else if (split_count(space_split[index_space]) == 1) //si il y a que un ">"
			{
				command_split[index_command] = space_split[index_space];
				index_command++;
			}
		}
		else if (redir_out > 0) //si il est en plein milieu
		{
			token_split = ft_split_sep(space_split[index_space], '>');
//			for (int j = 0; j < split_count(space_split[index_space]); ++j) {
//				printf("token: %s\n", token_split[j]);
//			}
			while (token_split[index_token])				// je mets chaque element de split token dans la commande general
				command_split[index_command++] = token_split[index_token++];
			free(token_split);
		}
		index_token = 0;
	}
	printf("Index space: %d\n", index_space);
	for (int j = 0;
		 j < split_count(command)
		 ; ++j) {
		printf("command: %s\n", command_split[j]);
	}
	return command_split;
}