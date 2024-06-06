/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testopenredir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:07:32 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/06 16:08:31 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//je teste si les fichiers s'ouvrent avant de vraiment les ouvrir
int testopening(t_token *tokens, t_tree *tree, t_node *nodes)
{
    int isredir;

    isredir = 0;
    while(nodes)
    {
        find_redir_in(tokens, tree, nodes, &isredir);
        find_redir_out(tokens, tree, nodes, &isredir);
        find_redir_append(tokens, tree, nodes, &isredir);
        if(tree->fdout != -1)
        {
            close(tree->fdout);
            tree->fdout =-1;
        }
        if(tree->fdin != -1)
        {
            close(tree->fdin);
            tree->fdin = -1;
        }
        nodes = nodes->right;
    }
    return (isredir);
}

// je teste si j'ai une redirection sur ma branche
int testredir(t_node *nodes)
{
    while(nodes)
    {
        if(nodes->type == TOKEN_REDIR_APPEND || nodes->type == TOKEN_REDIR_IN
            || nodes->type == TOKEN_REDIR_OUT)
        {
            return(1);    
        }
        nodes = nodes->right;
    }
    return(0);
}