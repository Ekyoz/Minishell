/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/05/13 16:15:36 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset(t_node *nodes, t_env **env)
{
    t_env *prev;
    t_env *actual;

    actual = *env;
    prev = NULL;
    if(nodes->args[1])
    {
        while(actual)
        {
            // si la variable de mon path vaut une valeur presente dans l'environnement
            if(!ft_strncmp(nodes->args[1], actual->value, ft_strlen(nodes->args[1])))
            {
                if(prev)
                {
                    // fprintf(stderr, "prev %s \n next %s\n", prev->value, actual->next->value);
                    prev->next = actual->next;
                }
                else
                {
                    *env = actual->next;
                }
                free(actual);
                return(0);
            }
            else
            {
                prev = actual;
                actual = actual->next;
            }
        }
    }
    return(1);
}

int unset_export(t_node *nodes, t_env *env)
{
    if(!ft_strncmp(nodes->args[0], "unset", 5))
    {
        unset(nodes, &env);
        // displayenv(env);
        return(1);
    }
    else if(!ft_strncmp(nodes->args[0], "export", 5))
    {
        return(1);
    }
    else
        return(0);
}

