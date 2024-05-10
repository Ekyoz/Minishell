/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/05/10 17:14:19 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void unset(t_node *nodes, t_env *env)
{
    t_env *prev;

    prev = NULL;
    if(nodes->args[1])
    {
        while(env)
        {
            // si la variable de mon path vaut une valeur presente dans l'environnement
            if(!ft_strncmp(nodes->args[1], env->value, ft_strlen(nodes->args[1])))
            {
                fprintf(stderr, "la je suis dans le bon arg\n");
                if(prev)
                {
                    prev->next = env->next;
                    free(env);
                    env = prev->next;
                }
                else
                {
                    prev = env->next;
                    free(env);
                    env = prev;
                }
            }
            else
            {
                prev = env;
                env = env->next;
            }
        }
    }
    exit(0);
}
