/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:33:55 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/30 15:26:35 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void sig_handler_heredoc(int sig)
{
    if(sig == SIGINT) // ctrl + c
    {
        fprintf(stderr, "mec faut signal quit la\n");
        ft_putstr_fd("\n", 1);
        signal_status = 130;
        // exit(1);
        // return((void)1);
    }
}

void set_signal_heredoc(void)
{
    // struct sigaction sig;
    
    // sigemptyset(&sig.sa_mask);
    // sig.sa_flags = 0;
    // sig.sa_handler = sig_handler_heredoc;

    // if(sigaction(SIGINT, &sig, NULL) == -1)
    // {
    //     perror("Error ctrl + c\n");
    //     exit(0);
    // }
    signal(SIGINT, sig_handler_heredoc);
    signal(SIGQUIT, SIG_IGN);
}
