/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:43:01 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/28 15:53:44 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void print_error(int errorcode, t_tree *tree, t_node *node)
{
    if(errorcode == 1) // Erreur ouverture de fichiers et de permission
    {
        tree->error[0] = 1;
        perror(node->args[0]);
        exit(1);
    }
    if(errorcode == 2) // command not found
    {
        if(tree->fdin != -1)
            close(tree->fdin);
        if(tree->fdout != -1)
        {
            if(dup2(tree->fdoutcp, STDOUT_FILENO) == -1)
                err_free_all(tree);
            close(tree->fdoutcp);
        }
        ft_putstr_fd(node->args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
    }
    if(tree->fdout != -1)
        close(tree->fdout);
    if(tree->fdoutcp != -1)
        close(tree->fdoutcp);
    free_tree(&tree);
    exit(127);
}

void err_free_all(t_tree *tree)
{
    free_tree(&tree);
    signal_status = 1;
    exit(1);
}

void malloc_tree_err(t_env *env)
{
    free_env(env);
    signal_status = 1;
    exit(1);
}

void command_not_found(t_tree *tree, char *cmd)
{
    (void)tree;
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd("command not found\n", 2);
    // free_tree(&tree);
    signal_status = 1;
}


