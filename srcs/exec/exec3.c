/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:24:45 by bastpoy           #+#    #+#             */
/*   Updated: 2024/06/21 15:07:36 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_cmd(t_tree *tree, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (checkj(tree->indexj, j))
			parent_process(tree->status, tree->pid[j], 0);
		j++;
	}
}

static void	close_pipe(t_tree *tree, int k, int i)
{
	if (tree->indexj[k] > 0)
		close(tree->fdpipe[tree->indexj[k] - 1][0]);
	if (tree->indexj[k] < i)
		close(tree->fdpipe[tree->indexj[k]][1]);
}

void	execute_cmd(t_tree *tree, t_token *tokens, t_node *nodes, int i)
{
	int	k;
	int	j;

	j = 0;
	k = 0;
	nodes = tree->nodes;
	while (j <= i)
	{
		if (j == tree->indexj[k])
		{
			tree->nodebegin = nodes;
			tree->pid[tree->indexj[k]] = do_fork(tree,
					tree->pid[tree->indexj[k]]);
			dup_and_exec(tokens, tree, i, j);
			close_pipe(tree, k, i);
			k++;
		}
		if (nodes->right)
			nodes = nodes->right;
		if (j == tree->indexj[k])
			k++;
		j++;
	}
	wait_cmd(tree, i);
}
