/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:52:50 by atresall          #+#    #+#             */
/*   Updated: 2024/06/18 15:49:03 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parsing(t_token **head, char *commands, t_env *env)
{
	char	**c_pipe;
	char	**c_splitted;
	int		i_pipe;

	i_pipe = -1;
	if (commands && *commands && check_input(commands))
	{
		c_pipe = pipe_splitter(commands);
		if (!c_pipe)
			return (free_token(c_pipe, NULL, NULL, NULL), false);
		if (!check_command(c_pipe))
			return (false);
		while (c_pipe[++i_pipe])
		{
			c_splitted = splitter(c_pipe[i_pipe], env);
			if (!c_splitted)
				return (free_token(c_pipe, c_splitted, NULL, NULL));
			parsing_redir(head, c_pipe, c_splitted, &i_pipe);
			if (i_pipe < pipe_counter(commands) - 1)
				append_token(head, TOKEN_PIPE, NULL);
		}
		free_array(&c_pipe);
	}
	return (checker(head));
}
