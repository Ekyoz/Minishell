/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:52:50 by atresall          #+#    #+#             */
/*   Updated: 2024/06/17 14:55:34 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing_redir(t_token **head, char **c_pipe, char **c_splitted,
				int *i_pipe);
static void	append_token_redir(char **c_redirs, char **c_splitted,
				t_token **head);

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
		while (c_pipe[++i_pipe])
		{
			c_pipe[i_pipe] = check_space(c_pipe[i_pipe]);
			c_splitted = splitter(c_pipe[i_pipe], env);
			if (!c_splitted)
				return (free_token(c_pipe, c_splitted, NULL, NULL));
			parsing_redir(head, c_pipe, c_splitted, &i_pipe);
			if (i_pipe < pipe_counter(commands) - 1)
				append_token(head, TOKEN_PIPE, NULL);
		}
		free_array(&c_pipe);
	}
	checker(head);
	return (true);
}

static void	parsing_redir(t_token **head, char **c_pipe, char **c_splitted,
		int *i_pipe)
{
	char	**c_cmd;
	char	**c_redirs;

	c_redirs = NULL;
	c_cmd = NULL;
	if (!there_token(c_pipe[*i_pipe]))
		append_token(head, TOKEN_WORD, c_splitted);
	else if (there_token(c_pipe[*i_pipe]))
	{
		c_redirs = redir(c_splitted);
		c_cmd = miss_elements(c_splitted);
		append_token(head, TOKEN_WORD, c_cmd);
		append_token_redir(c_redirs, c_splitted, head);
	}
	free_array(&c_splitted);
	free_token(NULL, c_redirs, c_cmd, NULL);
}

static void	append_token_redir(char **c_redirs, char **c_splitted,
		t_token **head)
{
	int		i_redirs;
	char	**value_temp;

	i_redirs = -1;
	while (c_redirs[++i_redirs])
	{
		if (is_token(c_redirs[i_redirs], 0) == TOKEN_REDIR_HEREDOC)
		{
			if (do_expand(c_splitted, (int)ft_arrlen(c_splitted)
					- ft_arrlen(c_redirs) + (i_redirs * 2) - 1))
			{
				value_temp = string_to_array("1");
				append_token(head, is_token(c_redirs[i_redirs], 0), value_temp);
				free_array(&value_temp);
			}
			else
				append_token(head, is_token(c_redirs[i_redirs], 0), NULL);
		}
		else
		{
			value_temp = string_to_array(c_redirs[i_redirs]);
			append_token(head, is_token(c_redirs[i_redirs], 0), value_temp);
			free_array(&value_temp);
		}
	}
}
