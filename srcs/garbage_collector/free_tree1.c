/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:43:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/23 11:32:00 by bpoyet           ###   ########.fr       */
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

void free_pipe(t_tree *tree)
{
    int i;

    i = 0;

    while(tree->nodes->type == TOKEN_PIPE)
    {
        i++;
        tree->nodes = tree->nodes->right;
    }
    while(i > 0)
    {
        free(tree->fdpipe[i - 1]);
        i--;
    }
    free(tree->fdpipe);
}