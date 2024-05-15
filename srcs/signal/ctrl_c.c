/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:52:31 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/15 17:33:56 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void sig_handler(int sig)
{
    // printf("le signal vaut %d\n", sig);
    if(sig == SIGINT) // ctrl + c
    {
        write(2, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        // fprintf(stderr, "signal var %d\n", signal_status);
        // exit(0);
    }
    if(sig == SIGQUIT) // ctrl + backslash
    {
        // printf("Dans le sigquit\n");
        // exit(0);
    }
}

void set_signal_cmd(int sig)
{
    fprintf(stderr, "est ce aue je rentre au moins la\n");
    if(sig == SIGINT) // ctrl + c
    {
        fprintf(stderr, "dans le sig cmd\n");
        exit(0);
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
    // if(sigaction(SIGQUIT, &sig, NULL) == -1)
    // {
    //     perror("Error ctrl + \\");
    //     exit(0);
    // }
}