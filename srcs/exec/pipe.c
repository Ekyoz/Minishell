/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:43:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/21 15:21:09 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_fdpipe(t_tree *tree, t_node *nodes)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (nodes->type == TOKEN_PIPE)
	{
		i++;
		if (i > 1000)
			err_free_all(tree);
		nodes = nodes->right;
	}
	tree->fdpipe = (int **)malloc(sizeof(int *) * i);
	if (!tree->fdpipe)
		err_free_all(tree);
	while (j < i)
	{
		tree->fdpipe[j] = malloc(sizeof(int) * 2);
		if (!tree->fdpipe[j])
			err_free_all(tree);
		if (pipe(tree->fdpipe[j]) == -1)
			err_free_all(tree);
		j++;
	}
	return (i);
}

void	parent_process_pipe(t_node **node)
{
	if ((*node)->right)
		(*node) = (*node)->right;
}

void	dup_pipe(t_token *tokens, t_tree *tree, int j, int i)
{
	if (tree->fdincp != -1)
		close(tree->fdincp);
	if (tree->fdin != -1)
		close(tree->fdin);
	if (j == 0)
	{
		first_pipe(tokens, tree, tree->nodebegin->left);
	}
	else if (j == i)
	{
		last_pipe(tokens, tree, tree->nodebegin, j);
	}
	else
	{
		mid_pipe(tokens, tree, tree->nodebegin->left, j);
	}
	close_all_pipes(tree->fdpipe, i);
}

int	checkj(int *indexj, int j)
{
	int	i;

	i = 0;
	while (indexj[i] != -1)
	{
		if (indexj[i] == j)
			return (1);
		i++;
	}
	return (0);
}

void	exec_pipe(t_token *tokens, t_tree *tree, t_node *nodes)
{
	int	i;

	tree->status = 0;
	i = init_fdpipe(tree, nodes);
	tree->indexj = (int *)malloc((i + 2) * sizeof(int));
	if (!tree->indexj)
		err_free_all(tree);
	tree->indexj[0] = -1;
	if (execute_heredoc(tree, tokens, nodes, i) == -1)
		return ;
	execute_cmd(tree, tokens, nodes, i);
}
