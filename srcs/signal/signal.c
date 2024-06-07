/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:52:31 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/05 18:40:34 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void sig_handler(int sig)
{
    if(sig == SIGINT) // ctrl + c
    {
        signal_status = 130;
        ft_putchar_fd('\n', 2);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void set_signal(void)
{
    // struct sigaction sig;
    
    // sigemptyset(&sig.sa_mask);
    // sig.sa_flags = 0;
    // sig.sa_handler = sig_handler;

    // if(sigaction(SIGINT, &sig, NULL) == -1)
    // {
    //     perror("Error ctrl + c");
    //     exit(0);
    // }
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
}
void get_signal_cmd(int status, pid_t pid)
{
    waitpid(pid, &status, 0);
    // if(WIFSIGNALED(status))
    // {
    //     signal_status = WTERMSIG(status);
    // }

    if(WIFEXITED(status))
    {
        signal_status = WEXITSTATUS(status);
    }
}
void hdoc_or_cmd(t_node *nodes)
{
    if(is_heredoc(nodes))
        set_signal_heredoc();
    else
        set_signal_cmd();    
}   