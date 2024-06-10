/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:43:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/07 12:34:55 by bastpoy          ###   ########.fr       */
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

void ft_exit(t_tree *tree)
{
    ft_putstr_fd("exit\n", 2);
    free_tree(&tree, 1);
    exit(g_signal_status);
}
void free_tree_tokens(t_tree **tree, t_token *tokens)
{
    clear_token(&tokens);
    free_tree(tree, 1);
}