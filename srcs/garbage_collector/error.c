/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:43:01 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/23 14:37:11 by bpoyet           ###   ########.fr       */
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
        exit(1);
    }
    // command not found
    if(errorcode == 2)
    {
        // fprintf(stderr, "la valeur de fdout %d\n", tree->fdout);
        if(tree->fdin != -1)
            close(tree->fdin);
        if(tree->fdout != -1)
        {
            dup2(tree->fdoutcp, STDOUT_FILENO);
            // close(tree->fdout);
            close(tree->fdoutcp);
        }
        printf("%s: Command not found\n", node->args[0]);
    }
	if(errorcode == 3)
	{
		printf("Quote not close\n");
	}
    if(tree->fdout != -1)
        close(tree->fdout);
    if(tree->fdoutcp != -1)
        close(tree->fdoutcp);
    free_tree(&tree);
    exit(127);
}

void malloc_err(t_tree *tree)
{
    free_tree(&tree);
    exit(1);
}

void malloc_tree_err(t_env *env)
{
    free_env(env);
    exit(1);
}

