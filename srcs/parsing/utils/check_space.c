/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <atresall@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:46:09 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/07 15:46:09 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_redir_append_heredoc(char *cmd, int i);
static char	*handle_redir_out_in(char *cmd, int i);

char	*check_space(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (is_token(cmd, i) == TOKEN_REDIR_APPEND || is_token(cmd,
				i) == TOKEN_REDIR_HEREDOC)
		{
			cmd = handle_redir_append_heredoc(cmd, i);
			i += 2;
		}
		else if (is_token(cmd, i) == TOKEN_REDIR_OUT || is_token(cmd,
				i) == TOKEN_REDIR_IN)
		{
			cmd = handle_redir_out_in(cmd, i);
			i += 1;
		}
	}
	return (cmd);
}

static char	*handle_redir_append_heredoc(char *cmd, int i)
{
	char	*sub;
	char	*sub2;
	char	*join;
	char	*temp;

	if (cmd[i + 2] != ' ')
	{
		sub = ft_substr(cmd, 0, i + 2);
		sub2 = ft_substr(cmd, i + 2, ft_strlen(cmd) - i - 2);
		join = ft_strjoin(" ", sub2);
		temp = cmd;
		cmd = ft_strjoin(sub, join);
		free_chars(sub, sub2, join, temp);
	}
	if (i > 0 && cmd[i - 1] != ' ')
	{
		sub = ft_substr(cmd, 0, i);
		sub2 = ft_substr(cmd, i, ft_strlen(cmd) - i);
		join = ft_strjoin(" ", sub2);
		temp = cmd;
		cmd = ft_strjoin(sub, join);
		free_chars(sub, sub2, join, temp);
	}
	return (cmd);
}

static char	*handle_redir_out_in(char *cmd, int i)
{
	char	*sub;
	char	*sub2;
	char	*join;
	char	*temp;

	if (cmd[i + 1] != ' ')
	{
		sub = ft_substr(cmd, 0, i + 1);
		sub2 = ft_substr(cmd, i + 1, ft_strlen(cmd) - i - 1);
		join = ft_strjoin(" ", sub2);
		cmd = ft_strjoin(sub, join);
		free_chars(sub, sub2, join, NULL);
	}
	if (i > 0 && cmd[i - 1] != ' ')
	{
		sub = ft_substr(cmd, 0, i);
		sub2 = ft_substr(cmd, i, ft_strlen(cmd) - i);
		join = ft_strjoin(" ", sub2);
		temp = cmd;
		cmd = ft_strjoin(sub, join);
		free_chars(sub, sub2, join, temp);
	}
	return (cmd);
}
