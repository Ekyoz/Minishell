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

static void	parsing_redir(t_token **head, char **c_pipe, char **c_splitted,
				int *i_pipe);
static void	append_token_redir(char **c_redirs,	t_token **head, int *ex_here);
static int *expand_heredoc_parsing(char **c_pipe, int i_pipe);
static int count_heredoc(char *cmd);

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
		c_cmd = miss_elements(c_splitted, c_redirs);
		append_token(head, TOKEN_WORD, c_cmd);
		append_token_redir(c_redirs, head, expand_heredoc_parsing(c_pipe, *i_pipe));
	}
	free_token(c_splitted, c_redirs, c_cmd, NULL);
}

static void	append_token_redir(char **c_redirs, t_token **head, int *ex_here)
{
	int		i_redirs;
	char	**value_temp;

	i_redirs = -1;
	while (c_redirs[++i_redirs])
	{
		if (is_token(c_redirs[i_redirs], 0) == TOKEN_REDIR_HEREDOC)
		{
			if (ex_here[i_redirs+1] == i_redirs)
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
	free(ex_here);
}

static int *expand_heredoc_parsing(char **c_pipe, int i_pipe)
{
	int i = -1;
	int herdoc_pos = 0;
	int i_pos = 1;
	int *pos;

	pos = (int *) malloc(sizeof(int) * (count_heredoc(c_pipe[i_pipe])+1));
	ft_memset(pos, -1, sizeof(int) * (count_heredoc(c_pipe[i_pipe])+1));
	pos[0] = count_heredoc(c_pipe[i_pipe])+1;
	while(c_pipe[i_pipe][++i])
	{
		if (is_token(c_pipe[i_pipe], i) == TOKEN_REDIR_HEREDOC)
		{
			if (c_pipe[i_pipe][i+2] == ' ')
			{
				if (c_pipe[i_pipe][i+3] == '\'' || c_pipe[i_pipe][i+3] == '"')
				{
					pos[i_pos++] += count_heredoc(c_pipe[i_pipe]) - herdoc_pos;
					herdoc_pos += 2;
				}
			}
			else
			{
				if (c_pipe[i_pipe][i+2] == '\'' || c_pipe[i_pipe][i+2] == '"')
				{
					pos[i_pos++] += count_heredoc(c_pipe[i_pipe]) - herdoc_pos;
					herdoc_pos += 2;
				}
			}
		}
	}
	return pos;
}

static int count_heredoc(char *cmd)
{
	int i = -1;
	int count = 0;

	while(cmd[++i])
	{
		if (is_token(cmd, i) == TOKEN_REDIR_HEREDOC)
		{
			i += 2;
			count ++;
		}
	}
	return count;
}