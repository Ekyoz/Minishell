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
	return (TOKEN_WORD);
}

bool	there_token(char *command)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		if (ft_strnstr(command, ">>", ft_strlen(command)))
			return (true);
		if (ft_strnstr(command, "<<", ft_strlen(command)))
			return (true);
		if (command[i] == '>')
			return (true);
		if (command[i] == '<')
			return (true);
	}
	return (false);
}
