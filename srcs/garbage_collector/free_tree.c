/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:14:56 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/23 11:56:14 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_nodes_args(t_node *node)
{
    int i;

    i = 0;
    if(node->args)
    {
        while(node->args[i])
        {
            if(node->args[i])
                free(node->args[i]);
            i++;
        }
        free(node->args);
        node->args = NULL;
    }
}

static void free_r_l(t_node *node, t_node *nodecp)
{
    while(node)
    {
        nodecp = node;
        free_nodes_args(node); // je free les elements de la structure 
        if(node->left) // je free si il y a un element a gauche
        {
            free_nodes_args(node->left);
            free(node->left);
        }
        node = node->right; // je passe sur l'element de droite
        free(nodecp); // je free le node actuelle
    }
}

static void free_nodes(t_node *nodes)
{
    t_node *nodecp;
    t_node *nodecp1;
    t_node *nodebegin;

    nodecp = NULL;
    nodecp1 = nodes;
    nodebegin = nodes;
    if(nodes->right)
    {
        // nodecp = nodes->right;
        free_r_l(nodes->right, nodecp);
    }
    if(nodecp1->left)
    {
        // nodecp1 = nodecp1->left;
        free_r_l(nodecp1->left, nodecp1);
    }
    free_nodes_args(nodebegin);
    free(nodebegin);
}

static void free_envp(t_tree *tree)
{
    int i;

    i = 0;
    while(tree->envp[i])
    {
        free(tree->envp[i]);
        i++;
    }
    free(tree->envp);
}

void free_tree(t_tree **tree)
{
    if((*tree))
    {
        if((*tree)->fdpipe)
        {
            free_pipe((*tree));
            (*tree)->fdpipe = NULL;
        }
        if((*tree)->nodebegin)
        {
            free_nodes((*tree)->nodebegin);
            (*tree)->nodebegin = NULL;
            (*tree)->nodes = NULL;
        }
        if ((*tree)->env)
        {
            free_env((*tree)->env);
            (*tree)->env = NULL;
        }
        if((*tree)->envp)
        {
            free_envp((*tree));
            (*tree)->envp = NULL;
        }
        free((*tree));
        (*tree) = NULL;
    }
}
