/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:05:17 by atresall          #+#    #+#             */
/*   Updated: 2024/05/03 17:49:21 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int split_count(char *command) {
	int i = 0;
	int count = 0;
	bool in_word = false;

	if (ft_strlen(command) <= 2 && is_token(command, 0) != TOKEN_WORD)
		return 1;

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
				if (is_token(command, i) == TOKEN_REDIR_APPEND || is_token(command, i) == TOKEN_REDIR_HEREDOC)
					i+=2;
				else if (is_token(command, i) == TOKEN_REDIR_OUT || is_token(command, i) == TOKEN_REDIR_IN)
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

char **splitter(char *command)
{
	int i_space;
	int i_final;
	int i_token;
	char **c_space;
	char **c_token;
	char **c_final;

	i_space = -1;
	i_final = 0;
	i_token = -1;
	c_space = ft_split(command, ' ');
	c_final = (char **) malloc(sizeof(char *) * split_count(command)+1);

	while (c_space[++i_space])
	{
		if (!there_token(c_space[i_space])) // si il n'y a pas de token
			c_final[i_final++] = c_space[i_space];
		if (there_token(c_space[i_space])) // si il y a un token
		{
			c_token = split_token(c_space[i_space]);
			while (c_token[++i_token])
				c_final[i_final++] = c_token[i_token];
		}
	}
	c_final[i_final] = NULL;
	return c_final;
}
