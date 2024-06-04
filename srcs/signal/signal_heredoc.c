/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:33:55 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/31 23:55:05 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void err_null_heredoc(t_tree *tree, char **eofword, int i)
{
    ft_putstr_fd("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `", 2);
    ft_putstr_fd(eofword[i], 2);
    ft_putstr_fd("')\n", 2);
    free_array(eofword);
    err_free_all(tree);
}

static void sig_handler_heredoc(int sig)
{
    if(sig == SIGINT) // ctrl + c
    {
        ft_putchar_fd('\n', 0);
        signal_status = 130;
    }
}

void set_signal_heredoc(void)
{
    struct sigaction sig;
    
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_handler_heredoc;

    if(sigaction(SIGINT, &sig, NULL) == -1)
    {
        perror("Error ctrl + c\n");
        exit(0);
    }
    signal(SIGQUIT, SIG_IGN);
}
