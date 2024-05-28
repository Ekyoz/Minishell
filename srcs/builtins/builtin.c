/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:02:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/28 15:51:58 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retourne 1 si un builtin a bien ete trouve
// je me mets pas les builtin de unset et export car il modifie ma structure
// ils ne peuvent donc pas etre dans un fork() je les execute a part
int choose_builtin(t_tree *tree, t_node *nodes, t_env *env)
{
    if(!ft_strncmp(nodes->args[0], "pwd", 4))
    {
        getpwd_env(env);
        return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "unset", 6))
    {
        do_unset(nodes, tree->env);
        return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "export", 6))
    {
        do_export(tree, nodes);
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
        do_echo(nodes);
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
