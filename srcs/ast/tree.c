/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:11:51 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/21 13:56:43 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*init_tree(t_env *env)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		malloc_tree_err(env);
	tree->env = env;
	tree->fdin = -1;
	tree->fdout = -1;
	tree->fdoutcp = -1;
	tree->fdincp = -1;
	tree->fdpipe = NULL;
	tree->indexj = NULL;
	tree->error[0] = 0;
	tree->error[1] = 0;
	tree->error[2] = 0;
	tree->error[3] = 0;
	tree->pid[0] = 0;
	tree->pid[1] = 0;
	tree->pid[2] = 0;
	tree->repeatstatus = 0;
	tree->nodebegin = NULL;
	tree->head = NULL;
	tree->expandheredoc = 0;
	get_env_args(env_to_string(tree, tree->env), tree);
	return (tree);
}
