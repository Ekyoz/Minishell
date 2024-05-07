/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:43:01 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/07 17:44:34 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error(int errorcode, t_node *node, t_tree *tree)
{
    if(errorcode = 1 && tree->error[1] == 1) // command not found
    {
        Printf("Command not found: %s\n", node->args[0]);
        exit(errno);
    }
}

void check_error_code(t_tree *tree)
{
    if(tree->error[0] == 1) // erreur d'ouverture de fichiers
    {
        perror("");
        exit(errno);
    }
}