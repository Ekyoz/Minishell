/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:33:55 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/06 16:19:10 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void err_null_heredoc(t_token *tokens, t_tree *tree, char **eofword, int *i)
{
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `", 2);
    ft_putstr_fd(eofword[*i], 2);
    ft_putstr_fd("')\n", 2);
    *i = *i + 1;
    if(eofword[*i] == NULL)
    {
        free_array(eofword);
        free_tree_tokens(&tree, tokens);
        exit(0);
    }
}

static void sig_handler_heredoc(int sig)
{
    if(sig == SIGINT) // ctrl + c
    {
        ft_putchar_fd('\n', 0);
        signal_status = 130;
    }

}

static void sigquit()
{
    ft_putstr_fd("\b\033[K", 0);
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
    signal(SIGQUIT, sigquit);
}
