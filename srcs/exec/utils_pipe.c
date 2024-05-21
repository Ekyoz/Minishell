/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:00:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/21 17:18:22 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_pipe(int fd1, int fd2, int fd3, int fd4)
{
    if(fd1 != -1)
        close(fd1);
    if(fd2 != -1)
        close(fd2);
    if(fd3 != -1)
        close(fd3);
    if(fd4 != -1)
        close(fd4);
}

void first_pipe(t_tree *tree, t_node *node)
{
    heredoc(tree, node);
    if(!check_redir_out(tree, node) && 
        !testopening(tree, node)) //si jai pas de redir out et une in
    {
        if(check_cmd1(tree, node)) //si j'ai un builtin ou une commande bonne
                dup2(tree->fdpipe[0][1], STDOUT_FILENO);
    }
    check_redir_in(tree, node);    
}

void last_pipe(t_tree *tree, t_node *node, int j)
{
    heredoc(tree, node);
    check_redir_out(tree, node);
    if(!check_redir_in(tree, node))
        dup2(tree->fdpipe[j - 1][0], STDIN_FILENO);
}

void mid_pipe(t_tree *tree, t_node *node, int j)
{
    heredoc(tree, node);
    if(!check_redir_in(tree, node))
        dup2(tree->fdpipe[j - 1][0], STDIN_FILENO); // je lis mon pipe actuelle
    if(!check_redir_out(tree, node) 
        && check_cmd1(tree, node))
        dup2(tree->fdpipe[j][1], STDOUT_FILENO);  
}