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

static void	handle_token_redir(char **l_final, char **cmd, int *i_split,
				int i_cmd);
static void	handle_token_append(char **l_final, char **cmd, int *i_split,
				int i_cmd);

char	**redir(char **cmd)
{
	int		i_cmd;
	int		i_split;
	char	**l_final;

	i_cmd = -1;
	i_split = 0;
	l_final = NULL;
	cmd = clean_space(cmd);
	l_final = (char **)malloc(sizeof(char *) * (ft_arrlen(cmd) * 2 + 1));
	ft_bzero(l_final, sizeof(char *) * (ft_arrlen(cmd) * 2 + 1));
	while (cmd[++i_cmd])
	{
		if ((is_token(cmd[i_cmd], 0) == TOKEN_REDIR_OUT || is_token(cmd[i_cmd],
					0) == TOKEN_REDIR_IN) && cmd[i_cmd + 1])
			handle_token_redir(l_final, cmd, &i_split, i_cmd);
		if ((is_token(cmd[i_cmd], 0) == TOKEN_REDIR_APPEND
				|| is_token(cmd[i_cmd], 0) == TOKEN_REDIR_HEREDOC)
			&& cmd[i_cmd + 1])
			handle_token_append(l_final, cmd, &i_split, i_cmd);
	}
	l_final[i_split] = NULL;
	return (clean_space(l_final));
}

static void	handle_token_redir(char **l_final, char **cmd, int *i_split,
		int i_cmd)
{
	l_final[*i_split] = ft_strdup(cmd[i_cmd]);
	l_final[*i_split + 1] = ft_strdup(" ");
	l_final[*i_split + 2] = ft_strdup(cmd[i_cmd + 1]);
	*i_split += 3;
}

static void	handle_token_append(char **l_final, char **cmd, int *i_split,
		int i_cmd)
{
	l_final[*i_split] = ft_strdup(cmd[i_cmd]);
	l_final[*i_split + 1] = ft_strdup(" ");
	l_final[*i_split + 2] = ft_strdup(cmd[i_cmd + 1]);
	*i_split += 3;
}
