/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:00:24 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/13 22:06:11 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

t_node *init_nodes(t_node *nodes)
{
    nodes = (t_node*)malloc(sizeof(t_node));
    if(!nodes)
    {
        perror("Malloc Error");
        return(NULL);
    }
    nodes->type = NULL;
    nodes->file_type = 0;
    nodes->tree_level = 0;
    nodes->args = NULL;
    nodes->left = NULL;
    nodes->right = NULL;
    return (nodes);
}