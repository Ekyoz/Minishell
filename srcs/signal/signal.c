/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:52:31 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/16 19:59:13 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void sig_handler(int sig)
{
    if(sig == SIGINT) // ctrl + c
    {
        signal_status = 130;
        write(2, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void set_signal(void)
{
    struct sigaction sig;
    
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_handler;

    if(sigaction(SIGINT, &sig, NULL) == -1)
    {
        perror("Error ctrl + c");
        exit(0);
    }
    signal(SIGQUIT, SIG_IGN);
}

void    empty_signal(int sig)
{
    (void)sig;
}