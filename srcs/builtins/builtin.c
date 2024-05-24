/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:02:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/24 13:03:30 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retourne 1 si un builtin a bien ete trouve
// je me mets pas les builtin de unset et export car il modifie ma structure
// ils ne peuvent donc pas etre dans un fork() je les execute a part
int choose_builtin(t_tree *tree, t_node *nodes, t_env *env)
{
    // fprintf(stderr, "node %s \n", nodes->args[0]);
    if(!ft_strncmp(nodes->args[0], "pwd", 4))
    {
        getpwd_env(env);
        return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "unset", 6))
    {
        unset_export(nodes, tree->env);
        return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "env", 4))
    {
        if(displayenv(env) == 1)
        {
            perror("");
            exit(errno);
        }
        else
            return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "cd", 3))
    {
        do_cd(tree, nodes);
        return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "echo", 5))
    {
        return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "exit", 5))
    {
        exit_function(tree, nodes);
        return(1);
    }
    // else if(!ft_strncmp(nodes->args[0], "$?", 3))
    // {
    //     read_status(tree);
    //     return(1);
    // }
    else
        return (0);
}