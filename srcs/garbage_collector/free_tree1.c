/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:43:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/22 17:48:20 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env(t_env *env)
{
    t_env *envcp;

    while(env)
    {
        envcp = env;
        if(env->value)
            free(env->value);
        env = env->next;
        free(envcp);
    }
}

void free_pipe(int **fdpipe)
{
    int i;

    i = 0;
    while(fdpipe[i])
    {
        free(fdpipe[i]);
        i++;
    }
    free(fdpipe);
}