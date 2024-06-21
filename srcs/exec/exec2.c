/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:05:00 by bastpoy           #+#    #+#             */
/*   Updated: 2024/06/21 14:05:39 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int execute_heredoc(t_tree *tree, t_node *nodes, int i)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (j <= i)
	{
		tree->nodebegin = nodes;
		if(nodes->type ==TOKEN_REDIR_HEREDOC || is_heredoc(nodes->left))
		{
			if (!do_heredoc(tree, j, i))
				return (-1);
			tree->pid[j] = do_fork(tree, tree->pid[j]);
			if (tree->pid[j] == 0)
			{
				dup_pipe(NULL, tree, j, i);
				exec(NULL, tree, nodes);
			}
			if (j > 0)
				close(tree->fdpipe[j - 1][0]);
			if (j < i)
				close(tree->fdpipe[j][1]);
		}
		else
		{
			tree->indexj[k] = j;
			k++;
			tree->indexj[k] = -1;
		}
		j = j + 1;
		parent_process_pipe(i, &j, tree, &nodes);
	}
	return(0);
}
