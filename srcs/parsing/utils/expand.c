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

int *get_no_expandable(char **cmd)
{
	int i = -1;
	int h = 0;
	int *no_expandable;

	no_expandable = (int *) malloc(sizeof (int) * (get_len_no_expand(cmd) + 1));
	no_expandable = ft_memset(no_expandable, -1, sizeof(int)*(get_len_no_expand(cmd)+1));

	while (cmd[++i])
		if (is_token(cmd[i], 0) == TOKEN_REDIR_HEREDOC)
			no_expandable[h++] = i+2;
	return no_expandable;
}

bool is_expandable(int *no_expandable, int pos)
{
	int i = -1;
	while(no_expandable[++i] != '\0')
	{
		if (no_expandable[i] == pos)
			return false;
	}
	return true;
}

int get_len_no_expand(char **cmd)
{
	int i = -1;
	int heredoc = 0;

	while(cmd[++i])
		if (is_token(cmd[i], 0) == TOKEN_REDIR_HEREDOC)
			heredoc++;
	return heredoc;
}