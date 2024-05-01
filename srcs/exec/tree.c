/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:11:51 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/01 11:06:02 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree *init_tree(char *envp[])
{
    t_tree *tree;

    tree = (t_tree*)malloc(sizeof(t_tree));
    if(!tree)
    {
        perror("Malloc error of tree");
        return(NULL);
    }
    //ERREUR A GERER DANS LE CAS OU IL NY A PAS DENVIRONNEMENT
    get_env_args(envp, tree);
    return(tree);
}