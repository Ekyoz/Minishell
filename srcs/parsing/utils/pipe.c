/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:38:06 by atresall          #+#    #+#             */
/*   Updated: 2024/05/17 13:38:06 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_counter(const char *command)
{
	int	i;
	int	pipe;
	bool quote = false;

	i = -1;
	pipe = 1;
	while (command[++i])
	{
		if (command[i] == '"' || command[i] == '\'')
			quote = !quote;
		if (command[i] == '|' && !quote)
			pipe++;
	}
	return (pipe);
}
