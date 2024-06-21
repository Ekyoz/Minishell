/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <atresall@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:24:14 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/21 17:24:14 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_token_redir(char **c_redirs, t_token **head, int *ex_here);
static int	*expand_heredoc_parsing(char **c_pipe, int i_pipe);
static void	app_token(char **c_redirs, t_token **head, int i_redirs,
				char *string);
static void	expand_here_utils(char *c_pipe, int i_list[3], int *pos, int n);

void	parsing_redir(t_token **head, char **c_pipe, char **c_splitted,
		int *i_pipe)
{
	char	**c_cmd;
	char	**c_redirs;

	c_redirs = NULL;
	c_cmd = NULL;
	if (!there_token(c_pipe, *i_pipe))
		append_token(head, TOKEN_WORD, c_splitted);
	else if (there_token(c_pipe, *i_pipe))
	{
		c_redirs = redir(c_splitted);
		c_cmd = miss_elements(c_splitted, c_redirs);
		append_token(head, TOKEN_WORD, c_cmd);
		append_token_redir(c_redirs, head, expand_heredoc_parsing(c_pipe,
				*i_pipe));
	}
	free_array(&c_cmd);
	free_array(&c_redirs);
	free_array(&c_splitted);
}

static void	append_token_redir(char **c_redirs, t_token **head, int *ex_here)
{
	int	i_redirs;
	int	ex_here_pos;

	i_redirs = -1;
	ex_here_pos = 1;
	while (c_redirs[++i_redirs])
	{
		if (is_token(c_redirs[i_redirs], 0) == TOKEN_REDIR_HEREDOC)
		{
			if (ex_here[ex_here_pos] == i_redirs)
			{
				app_token(c_redirs, head, i_redirs, "1");
				ex_here_pos++;
			}
			else
				append_token(head, is_token(c_redirs[i_redirs], 0), NULL);
		}
		else
			app_token(c_redirs, head, i_redirs, c_redirs[i_redirs]);
	}
	free(ex_here);
}

static void	app_token(char **c_redirs, t_token **head, int i_redirs,
		char *string)
{
	char	**value_temp;

	value_temp = string_to_array(string);
	append_token(head, is_token(c_redirs[i_redirs], 0), value_temp);
	free_array(&value_temp);
}

static int	*expand_heredoc_parsing(char **c_pipe, int i_pipe)
{
	int	i_list[3];
	int	*pos;

	i_list[0] = -1;
	i_list[1] = 0;
	i_list[2] = 1;
	pos = (int *)malloc(sizeof(int) * (count_heredoc(c_pipe[i_pipe]) + 1));
	ft_memset(pos, -1, sizeof(int) * (count_heredoc(c_pipe[i_pipe]) + 1));
	pos[0] = count_heredoc(c_pipe[i_pipe]) + 1;
	while (c_pipe[i_pipe][++i_list[0]])
	{
		if (is_token(c_pipe[i_pipe], i_list[0]) == TOKEN_REDIR_HEREDOC)
		{
			if (c_pipe[i_pipe][i_list[0] + 2] == ' ')
				expand_here_utils(c_pipe[i_pipe], i_list, pos, 3);
			else
				expand_here_utils(c_pipe[i_pipe], i_list, pos, 2);
		}
	}
	return (pos);
}

static void	expand_here_utils(char *c_pipe, int i_list[3], int *pos, int n)
{
	if (c_pipe[i_list[0] + n] == '\'' || c_pipe[i_list[0] + n] == '"')
	{
		pos[i_list[2]++] += count_heredoc(c_pipe) - i_list[1];
		i_list[1] += 2;
	}
}
