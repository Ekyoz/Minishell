/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <atresall@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:13:01 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/10 17:13:01 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**del_cmd(int first_quote[2], int last_quote[2], char **cmd)
{
	int	i;

	i = last_quote[0];
	while ((i - 1) >= first_quote[0])
		cmd = ft_arrdel(cmd, i--);
	return (cmd);
}

void	get_quoted_join(char **cmd, char **quoted, int last_quote[2], int i_cmd)
{
	char	*temp;
	char	*temp2;

	temp = *quoted;
	temp2 = ft_substr(cmd[i_cmd], 0, last_quote[1]);
	*quoted = ft_strjoin(*quoted, temp2);
	free(temp);
	free(temp2);
}
