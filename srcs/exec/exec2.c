/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:05:00 by bastpoy           #+#    #+#             */
/*   Updated: 2024/06/21 15:19:14 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_and_exec(t_token *tokens, t_tree *tree, int i, int j)
{
	if (tree->pid[j] == 0)
	{
		dup_pipe(tokens, tree, j, i);
		exec(tokens, tree, tree->nodebegin);
	}
}

static void	wait_heredoc_cmd(t_tree *tree, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (!checkj(tree->indexj, j))
			parent_process(tree->status, tree->pid[j], 0);
		j++;
	}
	if (access("./.here_doc", F_OK) != -1)
		unlink("./.here_doc");
}

static void	fill_array(int *array, int j, int *k)
{
	array[*k] = j;
	*k = *k + 1;
	array[*k] = -1;
}

static void	close_pipe(t_tree *tree, int j, int i)
{
	if (j > 0)
		close(tree->fdpipe[j - 1][0]);
	if (j < i)
		close(tree->fdpipe[j][1]);
}

int	execute_heredoc(t_tree *tree, t_token *tokens, t_node *nodes, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j <= i)
	{
		tree->nodebegin = nodes;
		if (nodes->type == TOKEN_REDIR_HEREDOC || is_heredoc(nodes->left))
		{
			if (!do_heredoc(tree, j, i))
				return (-1);
			tree->pid[j] = do_fork(tree, tree->pid[j]);
			dup_and_exec(tokens, tree, i, j);
			close_pipe(tree, j, i);
		}
		else
			fill_array(tree->indexj, j, &k);
		j = j + 1;
		parent_process_pipe(&nodes);
	}
	wait_heredoc_cmd(tree, i);
	return (0);
}
