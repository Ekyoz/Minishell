/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:02:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/31 20:01:46 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retourne 1 si un builtin a bien ete trouve
// je me mets pas les builtin de unset et export car il modifie ma structure
// ils ne peuvent donc pas etre dans un fork() je les execute a part
int choose_builtin(t_tree *tree, t_node *nodes)
{
    if(!ft_strncmp(nodes->args[0], "pwd", 4))
        return (do_pwd(tree, tree->env));
    else if(!ft_strncmp(nodes->args[0], "unset", 6))
        return(do_unset(nodes, tree->env));
    else if(!ft_strncmp(nodes->args[0], "export", 6))
        return(do_export(tree, nodes));
    else if(!ft_strncmp(nodes->args[0], "env", 4))
        return(displayenv(tree->env));
    else if(!ft_strncmp(nodes->args[0], "cd", 3))
        return (do_cd(tree, nodes));
    else if(!ft_strncmp(nodes->args[0], "echo", 5))
        return(do_echo(nodes));
    else if(!ft_strncmp(nodes->args[0], "exit", 5))
        return(do_exit(tree, nodes));
    else
        return (0);
}
