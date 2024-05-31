/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:00:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/31 12:04:16 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_all_pipes(int **fdpipe, int i)
{
    int j;

    j = 0;
    while(j < i)
    {
        close(fdpipe[j][0]);
        close(fdpipe[j][1]);
        j++;
    }
}

void first_pipe(t_tree *tree, t_node *node)
{
    heredoc(tree, node);
    if(!check_redir_out(tree, node) && 
        !testopening(tree, node)) //si jai pas de redir out et une in
    {
        // if(check_cmd1(tree, node)) //si j'ai un builtin ou une commande bonne
        // {
        if(dup2(tree->fdpipe[0][1], STDOUT_FILENO) == -1)
            err_free_all(tree);
        // }
    }
    check_redir_in(tree, node);    
}

void last_pipe(t_tree *tree, t_node *node, int j)
{
    heredoc(tree, node);
    check_redir_out(tree, node);
    if(!check_redir_in(tree, node))
    {
        if(dup2(tree->fdpipe[j - 1][0], STDIN_FILENO) == -1)
            err_free_all(tree);
    }
}

void mid_pipe(t_tree *tree, t_node *node, int j)
{
    heredoc(tree, node);
    if(!check_redir_in(tree, node))
    {
        if(dup2(tree->fdpipe[j - 1][0], STDIN_FILENO) == -1)
            err_free_all(tree); // je lis mon pipe actuelle
    }
    if(!check_redir_out(tree, node) 
        && check_cmd1(tree, node))
    {
        if(dup2(tree->fdpipe[j][1], STDOUT_FILENO) == -1)
            err_free_all(tree);
    }
}