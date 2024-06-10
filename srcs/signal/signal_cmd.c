/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:32:58 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/10 10:54:12 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler_cmd(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_signal_status = 130;
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		g_signal_status = 131;
	}
}

void	set_signal_cmd(void)
{
	signal(SIGINT, sig_handler_cmd);
	signal(SIGQUIT, sig_handler_cmd);
}
