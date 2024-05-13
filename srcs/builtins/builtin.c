/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:02:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/13 20:57:31 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retourne 1 si un builtin a bien ete trouve
int choose_builtin(t_node *nodes, t_env *env)
{
    // fprintf(stderr, "node %s \n", nodes->args[0]);
    if(!ft_strncmp(nodes->args[0], "pwd", 3))
    {
        getpwd_env(env);
        return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "unset", 5))
    {
        return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "env", 3))
    {
        if(displayenv(env) == 1)
        {
            perror("");
            exit(errno);
        }
        else
            return(1);
    }
    else
        return (0);
}