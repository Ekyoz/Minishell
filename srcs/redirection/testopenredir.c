/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testopenredir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:07:32 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/10 13:07:57 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//je teste si les fichiers s'ouvrent avant de vraiment les ouvrir
int testopening(t_tree *tree, t_node *nodes)
{
    int isredir;

    isredir = 0;
    while(nodes)
    {
        find_redir_in(tree, nodes, &isredir);
        find_redir_out(tree, nodes, &isredir);
        find_redir_append(tree, nodes, &isredir);
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