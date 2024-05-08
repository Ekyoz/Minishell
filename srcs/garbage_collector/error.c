/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:43:01 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/08 18:23:03 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error(int errorcode, t_tree *tree, t_node *node)
{
    // Erreur ouverture de fichiers et de permission
    if(errorcode == 1)
    {
        tree->error[0] = 1;
        perror(node->args[0]);
    }
    // command not found
    if(errorcode == 2)
    {
        if(tree->fdin != -1)
            close(tree->fdin);
        if(tree->fdout != -1)
        {
            dup2(tree->fdoutcp, STDOUT_FILENO);
            close(tree->fdoutcp);
        }
        printf("Command not found: %s\n", node->args[0]);
    }
    exit(errno);
}
