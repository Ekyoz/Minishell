/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <atresall@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:50:06 by alexandre         #+#    #+#             */
/*   Updated: 2024/05/31 14:50:17 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_no_expandable(char **cmd)
{
	int	i;
	int	h;
	int	*no_expandable;

	i = -1;
	h = 0;
	no_expandable = (int *)malloc(sizeof(int) * (get_len_no_expand(cmd) + 1));
	if (!no_expandable)
		return (NULL);
	no_expandable = ft_memset(no_expandable, -1, sizeof(int)
			* (get_len_no_expand(cmd) + 1));
	while (cmd[++i])
		if (is_token(cmd[i], 0) == TOKEN_REDIR_HEREDOC)
			no_expandable[h++] = i + 2;
	no_expandable[h] = '\0';
	return (no_expandable);
}

bool	is_expandable(int *no_expandable, int pos)
{
	int	i;

	i = -1;
	while (no_expandable[++i] != '\0')
	{
		if (no_expandable[i] == pos)
			return (false);
	}
	return (true);
}

bool	do_expand(char **split, int pos)
{
	if (pos + 2 > (int)ft_arrlen(split))
		return (false);
	if (split[pos + 2][0] != '\'' && split[pos + 2][0] != '"')
		return (true);
	return (false);
}

int	get_len_no_expand(char **cmd)
{
	int	i;
	int	heredoc;

	i = -1;
	heredoc = 0;
	while (cmd[++i])
		if (is_token(cmd[i], 0) == TOKEN_REDIR_HEREDOC)
			heredoc++;
	return (heredoc);
}
