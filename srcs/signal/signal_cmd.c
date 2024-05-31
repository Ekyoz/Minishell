/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:32:58 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/31 18:15:19 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void sig_handler_cmd(int sig)
{
    if(sig == SIGINT) // ctrl + c
    {
        write(1,"\n", 1);
        signal_status = 130;
        // exit(128 + sig);
    }
    if(sig == SIGQUIT)
    {
        write(2, "Quit (core dumped)\n", 19);
        signal_status = 131 ;
    }
    // else
    //     exit(128 + sig);
}

void set_signal_cmd(void)
{
    // struct sigaction sig;
    
    // sigemptyset(&sig.sa_mask);
    // sig.sa_flags = 0;
    // sig.sa_handler = sig_handler_cmd;

    // if(sigaction(SIGINT, &sig, NULL) == -1)
    // {
    //     perror("Error ctrl + c\n");
    //     exit(130);
    // }
    // if(sigaction(SIGQUIT, &sig, NULL) == -1)
    // {
    //     perror("Error SIGQUIT\n");
    //     exit(0);
    // }
    signal(SIGINT, sig_handler_cmd);
    signal(SIGQUIT, sig_handler_cmd);
}