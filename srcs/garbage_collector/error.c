/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:43:01 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/07 19:39:34 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error(int errorcode, t_node *node, t_tree *tree)
{
    if(errorcode == 1 && tree->error[0] == 0) // command not found
    {
        printf("Command not found: %s\n", node->args[0]);
        exit(errno);
    }
}

void check_error_code(t_tree *tree, t_node *node)
{
    // pour linstant erreur d'ouverture de fichiers et de permission
    tree->error[0] = 1;
    perror(node->args[0]);
    exit(errno);
}