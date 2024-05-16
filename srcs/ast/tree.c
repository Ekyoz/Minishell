/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:11:51 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/16 18:55:45 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree *init_tree(char *envp[], t_env *env)
{
    t_tree *tree;

    tree = (t_tree*)malloc(sizeof(t_tree));
    if(!tree)
    {
        perror("Malloc error of tree");
        return(NULL);
    }
    tree->env = env;
    tree->fdin = -1;
    tree->fdout = -1;
    tree->fdoutcp = -1;
    tree->error[0] = 0;
    tree->error[1] = 0;
    tree->error[2] = 0;
    tree->error[3] = 0;
    tree->repeatstatus = 0;
    //ERREUR A GERER DANS LE CAS OU IL NY A PAS DENVIRONNEMENT
    get_env_args(envp, tree);
    return(tree);
}
