/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:30:51 by atresall          #+#    #+#             */
/*   Updated: 2024/06/07 15:42:17 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	check_n(char **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[++i])
	{
		j = 0;
		if (args[i][j++] == '-' && args[i][j] && args[i][j] == 'n')
		{
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] && args[i][j] != 'n')
				return (1);
		}
		else
			return (i);
	}
	return (i);
}

int	do_echo(t_node *node)
{
	size_t	i;
	int		n;

	n = 1;
	if (!node->args[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	i = check_n(node->args);
	if (i > 1)
		n = 0;
	else
		n = 1;
	while (node->args[i])
	{
		ft_putstr_fd(node->args[i], 1);
		i++;
		if (node->args[i])
			ft_putchar_fd(' ', 1);
	}
	if (n)
		ft_putchar_fd('\n', 1);
	g_signal_status = 0;
	return (1);
}
