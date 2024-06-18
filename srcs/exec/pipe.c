/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:43:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/17 16:15:57 by bpoyet           ###   ########.fr       */
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

static void	parent_process_pipe(int i, int *j, t_tree *tree, t_node **node)
{
	if (*j > 0)
		close(tree->fdpipe[*j - 1][0]);
	if (*j < i)
		close(tree->fdpipe[*j][1]);
	*j = *j + 1;
	if ((*node)->right)
		(*node) = (*node)->right;
}

static void	dup_pipe(t_token *tokens, t_tree *tree, int j, int i)
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

void	exec_pipe(t_token *tokens, t_tree *tree, t_node *nodes)
{
	int	i;
	int	j;

	tree->status = 0;
	i = 0;
	j = 0;
	i = init_fdpipe(tree, nodes);
	while (j <= i)
	{
		tree->nodebegin = nodes;
		if (!do_heredoc(tokens, tree, j, i))
			return ;
		tree->pid[j] = do_fork(tree, tree->pid[j]);
		if (tree->pid[j] == 0)
		{
			dup_pipe(tokens, tree, j, i);
			exec(tokens, tree, nodes);
		}
		parent_process_pipe(i, &j, tree, &nodes);
	}
	wait_all_parent(tree, i);
}
