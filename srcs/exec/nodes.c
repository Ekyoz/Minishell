/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:30:32 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/18 15:39:02 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *add_node_left(t_node *nodes, t_token *token)
{
    nodes->left = init_nodes(); 
    nodes->left->type = token->type; // a gauche de la redirec c'est forcement une commande
    nodes->left->args = token->value; // je stocke la commande
    return (nodes);
}

t_node *add_node_right(t_node *nodes, t_token *token)
{
    nodes->right = init_nodes(); 
    nodes->right->type = token->type; // a gauche de la redirec c'est forcement une commande
    nodes->right->args = token->value; // je stocke la commande
    return (nodes);
}
t_node *add_node(t_node *nodes, t_token *token)
{
    nodes = init_nodes(nodes);
    nodes->type = token->type;
    nodes->args = token->value;
    return (nodes);
}

t_node *init_nodes()
{
    t_node *nodes;

    nodes = (t_node*)malloc(sizeof(t_node));
    if(!nodes)
    {
        perror("Malloc Error");
        return (NULL);
    }
    nodes->type = TOKEN_WORD;
    nodes->file_type = 0;
    nodes->tree_level = 0;
    nodes->args = NULL;
    nodes->left = NULL;
    nodes->right = NULL;
    return (nodes);
}