/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:52:50 by atresall          #+#    #+#             */
/*   Updated: 2024/05/07 15:40:18 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool parsing(t_token **head, char *commands)
{
	char **c_pipe = NULL; // command separer par la pipe
	char **c_splitted = NULL; // command separer par tous les tokens
	char **c_cmd = NULL; // list de la comamnde avec les flags
	char **c_args = NULL; // les elements qui sont pas les flags
	char **c_redirs = NULL; // liste des redirection et des fichiers
	int i_pipe = -1;
	int i_args;
	int i_redirs;
	if (commands)
	{
		c_pipe = pipe_splitter(commands);
		if (!c_pipe)
			return false;
		while (c_pipe[++i_pipe])
		{
			i_args = -1;
			i_redirs = -1;
			c_splitted = splitter(c_pipe[i_pipe]);
			if (!c_splitted)
				return false;
			if (!there_token(c_pipe[i_pipe])) // si il y a pas de redirection
			{
				if (c_splitted[0][0] == '-')
					return false;
				c_cmd = extract_flags(c_splitted);
				c_args = miss_elements(c_splitted, c_cmd);
				append_token(head, TOKEN_WORD, c_cmd);
				while (c_args[++i_args])
					append_token(head, TOKEN_WORD,string_to_array(c_args[i_args]));
			}
			else if (there_token(c_pipe[i_pipe]))// si il y a une/des redirections
			{
				c_redirs = redir(c_splitted);
				c_cmd = extract_flags(miss_elements(c_splitted, c_redirs));
				c_args = miss_elements(c_splitted, c_cmd);
				c_args = miss_elements(c_args, c_redirs);
				append_token(head, TOKEN_WORD, c_cmd);
				while (c_args[++i_args])
					append_token(head, TOKEN_WORD, string_to_array(c_args[i_args]));
				while (c_redirs[++i_redirs])
				{
					append_token(head,is_token(c_redirs[i_redirs], 0),string_to_array(c_redirs[i_redirs]));
				}
			}
			if (i_pipe < pipe_counter(commands) - 1)
				append_token(head, TOKEN_PIPE, NULL);
		}
	}
//	if (!checker(head, commands))
//		return false;
	return true;
}

