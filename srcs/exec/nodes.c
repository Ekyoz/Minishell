/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:30:32 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/30 12:42:09 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *add_node_left(t_node *nodes, t_token **token)
{
    nodes->left = init_nodes(); 
    nodes->left->type = (*token)->type; // a gauche de la redirec c'est forcement une commande
    nodes->left->args = (*token)->value; // je stocke la commande
    *token = (*token)->next;
    if((*token) != NULL && ((*token)->type == PIPEUSED || (*token)->type == REDIRUSED))
        (*token) = (*token)->next; // Je passe au prochain token
    return (nodes);
}

t_node *add_node_right(t_node *nodes, t_token **token, bool *is_redirec)
{
    nodes->right = init_nodes(); 
    nodes->right->type = (*token)->type; // a gauche de la redirec c'est forcement une commande
    nodes->right->args = (*token)->value; // je stocke la commande
   *token = (*token)->next;
    if((*token) != NULL && ((*token)->type == PIPEUSED || (*token)->type == REDIRUSED))
        (*token) = (*token)->next; // Je passe au prochain token
    *is_redirec = 0;
    return (nodes);
}

t_node *add_node(t_node *nodes, t_token **token)
{
    nodes->type = (*token)->type;
    nodes->args = (*token)->value;
    *token = (*token)->next;
    if((*token) != NULL && ((*token)->type == PIPEUSED || (*token)->type == REDIRUSED))
        (*token) = (*token)->next; // Je passe au prochain token
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

void add_branches(t_token *tokens, t_node **node, t_node **nodecp, bool *redir)
{
    *redir = 1;
    if(tokens != NULL)
    {
        (*nodecp)->right = init_nodes();
        (*nodecp) = (*nodecp)->right;
        *node = *nodecp;
    }
}
