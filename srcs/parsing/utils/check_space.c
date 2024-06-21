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
static bool	check_token(char *cmd);
static void	init_quote(int quote_list[2][2], char **cmd);

bool	check_command(char **cmd)
{
	int	i;
	int	j;
	int	quote_list[2][2];

	i = -1;
	init_quote(quote_list, cmd);
	while (cmd[++i] && (i <= quote_list[0][0] || i >= quote_list[1][0]))
	{
		j = -1;
		if (!check_token(cmd[i]))
			return (free_array(&cmd), false);
		while (cmd[i][++j] && (j < quote_list[0][1] || j > quote_list[1][1]))
		{
			if (get_int_type(is_token(cmd[i], j)) == 2)
			{
				cmd[i] = handle_redir_append_heredoc(cmd[i], j);
				j += 2;
			}
			else if (get_int_type(is_token(cmd[i], j)) == 1)
				cmd[i] = handle_redir_out_in(cmd[i], j++);
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

static bool	check_token(char *cmd)
{
	if (count_token(cmd) == 1)
	{
		if (is_token(cmd, get_int_type(is_token(cmd, 0))) == (t_token_type) - 1)
		{
			ft_putstr_fd(
				"minishell: syntax error near unexpected token `newline'\n", 2);
			return (false);
		}
	}
	if (is_token(cmd, ft_strlen(cmd) - 1) != TOKEN_WORD && is_token(cmd,
			ft_strlen(cmd)) == (t_token_type)-1)
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `newline'\n", 2);
		return (false);
	}
	return (true);
}

static void	init_quote(int quote_list[2][2], char **cmd)
{
	char	c_quote;

	quote_list[0][0] = (int)ft_arrlen(cmd);
	quote_list[0][1] = (int)ft_strlen(cmd[0]) * 2;
	quote_list[1][0] = (int)ft_arrlen(cmd);
	quote_list[1][1] = (int)ft_strlen(cmd[0]) * 2;
	if (quoted(cmd))
	{
		get_first_quote(cmd, quote_list[0], &c_quote, (int [2]){-1, -1});
		get_last_quote(cmd, quote_list[1], &c_quote, (int [2]){-1, -1});
	}
}
