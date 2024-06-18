/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:52:31 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/12 14:18:26 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_ctrld(t_env *env)
{
	ft_putstr_fd("exit\n", 1);
	free_env(env);
	exit(0);
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 130;
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	get_signal_cmd(int status, pid_t pid)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_signal_status = WEXITSTATUS(status);
	}
}

void	hdoc_or_cmd(t_node *nodes)
{
	if (is_heredoc(nodes))
	{
		set_signal_heredoc();
	}
	else
		set_signal_cmd();
}
