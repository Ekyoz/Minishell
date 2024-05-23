/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:52:50 by atresall          #+#    #+#             */
/*   Updated: 2024/05/17 13:25:37 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void parsing_redir(t_token **head, t_env *env, char ***c_pipe, char ***c_splitted, int *i_pipe);

bool parsing(t_token **head, char *commands, t_env *env)
{
	char **c_pipe;
	char **c_splitted;

	int i_pipe = -1;
	if (commands)
	{
		c_pipe = pipe_splitter(commands);
		if (!c_pipe)
			return false;
		while (c_pipe[++i_pipe])
		{
			c_splitted = splitter(c_pipe[i_pipe]);
			if (!c_splitted)
				return false;
			parsing_redir(head, env, &c_pipe, &c_splitted, &i_pipe);
			if (i_pipe < pipe_counter(commands) - 1)
				append_token(head, TOKEN_PIPE, NULL, env);
		}
	}
    checker(head);
	return true;
}

static void parsing_redir(t_token **head, t_env *env, char ***c_pipe, char ***c_splitted, int *i_pipe)
{
	char **c_cmd;
	char **c_redirs;
	int i_redirs;

	i_redirs = -1;

	if (!there_token(*c_pipe[*i_pipe]))
		append_token(head, TOKEN_WORD, *c_splitted, env);
	else if (there_token(*c_pipe[*i_pipe]))
	{
		c_redirs = redir(*c_splitted);
		c_cmd = miss_elements(*c_splitted, c_redirs);
		append_token(head, TOKEN_WORD, c_cmd, env);
		while (c_redirs[++i_redirs])
		{
			append_token(head,is_token(c_redirs[i_redirs], 0),string_to_array(c_redirs[i_redirs]), env);
		}
	}
}
