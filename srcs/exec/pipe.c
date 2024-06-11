/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:43:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/11 18:57:30 by bpoyet           ###   ########.fr       */
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

static void	dup_pipe(t_token *tokens, t_tree *tree, int j, int i)
{
	if (j == 0)
	{
		first_pipe(tokens, tree, tree->nodebegin->left);
		close_all_pipes(tree->fdpipe, i);
	}
	else if (j == i)
	{
		last_pipe(tokens, tree, tree->nodebegin, j);
		close_all_pipes(tree->fdpipe, i);
	}
	else
	{
		mid_pipe(tokens, tree, tree->nodebegin->left, j);
		close_all_pipes(tree->fdpipe, i);
	}
}

static void	execute_pipe(t_token *tokens, t_tree *tree, t_node *node)
{
	if (choose_builtin(tokens, tree, node))
	{
		free_tree(&tree, 1);
		clear_token(&tokens);
		exit(0);
	}
	if (!check_cmd1(tree, node))
		print_error(tokens, CMD_NOT_FOUND, tree, node);
	ft_execve(tree, node);
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
		hdoc_or_cmd(nodes->left);
		tree->pid[j] = do_fork(tree, tree->pid[j]);
		if (tree->pid[j] == 0)
		{
			dup_pipe(tokens, tree, j, i);
			tree->nodebegin = nodes;
			if (testredir(nodes->left))
				execute_pipe(tokens, tree, nodes->left->left);
			else if (nodes->left)
				execute_pipe(tokens, tree, nodes->left);
			else
				execute_pipe(tokens, tree, nodes);
		}
		parent_process_pipe(i, &j, tree, &nodes);
	}
	wait_all_parent(tree, i);
}
