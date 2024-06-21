/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:58:20 by atresall          #+#    #+#             */
/*   Updated: 2024/05/14 14:31:16 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	is_token(char *c, int pos)
{
	if (c[pos] == '>' && c[pos + 1] == '>')
		return (TOKEN_REDIR_APPEND);
	else if (c[pos] == '<' && c[pos + 1] == '<')
		return (TOKEN_REDIR_HEREDOC);
	else if (c[pos] == '>')
		return (TOKEN_REDIR_OUT);
	else if (c[pos] == '<')
		return (TOKEN_REDIR_IN);
	else if (c[pos] == '\0')
		return (-1);
	return (TOKEN_WORD);
}

bool	there_token(char **command, int pos)
{
	int	i;

	i = -1;
	while (command[pos][++i])
	{
		if (ft_strnstr(command[pos], ">>", ft_strlen(command[pos])))
			return (true);
		if (ft_strnstr(command[pos], "<<", ft_strlen(command[pos])))
			return (true);
		if (command[pos][i] == '>')
			return (true);
		if (command[pos][i] == '<')
			return (true);
	}
	return (false);
}

int	count_token(char *command)
{
	int	i;
	int	cout;

	i = -1;
	cout = 0;
	while (command[++i])
	{
		if (command[i] == '<')
		{
			if (command[i + 1] == '<')
				i++;
			cout++;
		}
		if (command[i] == '>')
		{
			if (command[i + 1] == '>')
				i++;
			cout++;
		}
	}
	return (cout);
}

int	get_int_type(t_token_type type)
{
	if (type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC)
		return (2);
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT)
		return (1);
	return (0);
}

int	count_heredoc(char *cmd)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (cmd[++i])
	{
		if (is_token(cmd, i) == TOKEN_REDIR_HEREDOC)
		{
			i += 2;
			count++;
		}
	}
	return (count);
}
