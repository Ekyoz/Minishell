/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:52:24 by bastpoy           #+#    #+#             */
/*   Updated: 2024/05/02 11:15:59 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void find_redir_out(t_tree *tree, t_node *nodes, int *isredir)
{
    if(nodes->type == TOKEN_REDIR_OUT)
    {
        if(nodes->right->type == TOKEN_REDIR_OUT || nodes->right->type == TOKEN_REDIR_OUT
            || nodes->right->type == TOKEN_REDIR_APPEND)
        {
            tree->fdout = open(nodes->right->left->args[0], O_TRUNC | O_CREAT | O_WRONLY, 0644);
            if(tree->fdout < 0)
                tree->error = 2;
        }
        else
        {
            tree->fdout = open(nodes->right->args[0], O_TRUNC | O_CREAT | O_WRONLY, 0644);
            if(tree->fdout < 0)
                tree->error = 2;                
        }
        *isredir = 1;
    }
}

void find_redir_in(t_tree *tree, t_node *nodes, int *isredir)
{
    if(nodes->type == TOKEN_REDIR_IN)
    {
        if(nodes->right->type == TOKEN_REDIR_IN || nodes->right->type == TOKEN_REDIR_OUT 
            || nodes->right->type == TOKEN_REDIR_APPEND)
        {
            tree->fdin = open(nodes->right->left->args[0], O_RDONLY, 0644);
            if(tree->fdin < 0)
                tree->error = 2;
        }
        else
        {
            tree->fdin = open(nodes->right->args[0], O_RDONLY, 0644);
            if(tree->fdin < 0)
                tree->error = 2;                
        }
        *isredir = 1;
    }
}

void find_redir_append(t_tree *tree, t_node *nodes, int *isredir)
{
    if(nodes->type == TOKEN_REDIR_APPEND)
    {
        if(nodes->right->type == TOKEN_REDIR_OUT || nodes->right->type == TOKEN_REDIR_OUT
            || nodes->right->type == TOKEN_REDIR_APPEND)
        {
            tree->fdout = open(nodes->right->left->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if(tree->fdout < 0)
                tree->error = 2;
        }
        else
        {
            tree->fdout = open(nodes->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if(tree->fdout < 0)
                tree->error = 2;                
        }
        *isredir = 1;
    }
}

int check_redir_out(t_tree *tree, t_node *nodes)
{
    int isredir;

    isredir = 0;
    // javance tant que j'ai des redirections out et j'ouvre les fichiers
    while(nodes)
    {
        find_redir_out(tree, nodes, &isredir);
        find_redir_append(tree, nodes, &isredir);
        nodes = nodes->right;
    }
    if(isredir == 1)
    {
        dup2(tree->fdout, STDOUT_FILENO);
        close(tree->fdout);
    }
    return (isredir);
}

int check_redir_in(t_tree *tree, t_node *nodes)
{
    int isredir;

    isredir = 0;
    // javance tant que j'ai des redirections out et j'ouvre les fichiers
    while(nodes)
    {
        find_redir_in(tree, nodes, &isredir);
        nodes = nodes->right;
    }
    if(isredir == 1)
    {
        dup2(tree->fdin, STDIN_FILENO);
        close(tree->fdin);
    }
    return (isredir);
}