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
static bool check_token(char *cmd);

bool check_command(char **cmd)
{
	int i;
	int	j;

	i = -1;

	while(cmd[++i])
	{
		j = -1;
		if (!check_token(cmd[i]))
			return (free_array(&cmd), false);
		while (cmd[i][++j])
		{
			if (is_token(cmd[i], j) == 2)
			{
				cmd[i] = handle_redir_append_heredoc(cmd[i], j);
				j += 2;
			}
			else if (is_token(cmd[i], j) == 1)
			{
				cmd[i] = handle_redir_out_in(cmd[i], j);
				j += 1;
			}
		}
	}
	return (true);
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

static bool check_token(char *cmd)
{
	if (count_token(cmd) == 1)
	{
		if (is_token(cmd, is_token(cmd, 0)) == (t_token_type)-1)
		{
			printf("Test un token");
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			return (false);
		}
	}
	if (is_token(cmd, ft_strlen(cmd)-1) != TOKEN_WORD && is_token(cmd, ft_strlen(cmd)) == (t_token_type )-1)
	{
		printf("Test manque un token apres");
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (false);
	}
	return true;
}