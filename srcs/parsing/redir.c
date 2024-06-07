/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:45:22 by atresall          #+#    #+#             */
/*   Updated: 2024/05/07 14:55:42 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **redir(char **cmd)
{
	int i_cmd = -1;
	int i_split = 0;
	char **l_final = NULL;

	cmd = clean_space(cmd);

	l_final = (char **) malloc( sizeof(char *) * (ft_arrlen(cmd)+2));
	ft_bzero(l_final, sizeof (char *)*(ft_arrlen(cmd)+1));

	while (cmd[++i_cmd])
	{
		if (is_token(cmd[i_cmd], 0) == TOKEN_REDIR_OUT ||
				is_token(cmd[i_cmd], 0) == TOKEN_REDIR_IN)
		{
			l_final[i_split] = ft_strdup(cmd[i_cmd]);
			l_final[i_split+1] = ft_strdup(" ");
			l_final[i_split+2] = ft_strdup(cmd[i_cmd+1]);
			i_split+=3;
		}
		if (is_token(cmd[i_cmd], 0) == TOKEN_REDIR_APPEND ||
			is_token(cmd[i_cmd], 0) == TOKEN_REDIR_HEREDOC)
		{
			l_final[i_split] = ft_strdup(cmd[i_cmd]);
			l_final[i_split+1] = ft_strdup(" ");
			l_final[i_split+2] = ft_strdup(cmd[i_cmd+1]);
			i_split+=3;
		}
	}
    l_final[i_split] = NULL;
	return clean_space(l_final);
}