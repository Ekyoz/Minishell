/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:43:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/21 14:18:13 by bastpoy          ###   ########.fr       */
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

void	parent_process_pipe(int i, int *j, t_tree *tree, t_node **node)
{
	// if (*j > 0)
	// 	close(tree->fdpipe[*j - 1][0]);
	// if (*j < i)
	// 	close(tree->fdpipe[*j][1]);
	// *j = *j + 1;
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

int checkj(int *indexj, int j)
{
	int i;

	i = 0;
	while(indexj[i] != -1)
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
	int	j;
	int k;

	tree->status = 0;
	k = 0;
	i = init_fdpipe(tree, nodes);
	tree->indexj = (int *)malloc((i + 1) * sizeof(int));
	if(!tree->indexj)
		err_free_all(tree);
	tree->indexj[0] = -1;
	// if(execute_heredoc(tree, nodes, i) == -1)
	// 	return ;
	// while (j <= i)
	// {
	// 	tree->nodebegin = nodes;
	// 	if(nodes->type ==TOKEN_REDIR_HEREDOC || is_heredoc(nodes->left))
	// 	{
	// 		// fprintf(stderr, "\033[0;34mcommande heredoc %d\033[0m\n", j);
	// 		if (!do_heredoc(tree, j, i))
	// 		{
	// 			return ;
	// 		}
	// 		tree->pid[j] = do_fork(tree, tree->pid[j]);
	// 		if (tree->pid[j] == 0)
	// 		{
	// 			dup_pipe(tokens, tree, j, i);
	// 			exec(tokens, tree, nodes);
	// 		}
	// 		if (j > 0)
	// 			close(tree->fdpipe[j - 1][0]);
	// 		if (j < i)
	// 			close(tree->fdpipe[j][1]);
	// 	}
	// 	else
	// 	{
	// 		indexj[k] = j;
	// 		k++;
	// 		indexj[k] = -1;
	// 	}
	// 	j = j + 1;
	// 	parent_process_pipe(i, &j, tree, &nodes);
	// }
	j = 0;
	k = 0;
	while (j <= i)
	{
		if(!checkj(tree->indexj, j))
			parent_process(tree->status, tree->pid[j], 0);
		j++;
	}
	if (access("./.here_doc", F_OK) != -1)
		unlink("./.here_doc");
	nodes = tree->nodes;
	k = 0;
	j = 0;
	while(j <= i)
	{
		if(j == tree->indexj[k])
		{
			tree->nodebegin = nodes;
			tree->pid[tree->indexj[k]] = do_fork(tree, tree->pid[tree->indexj[k]]);
			if (tree->pid[tree->indexj[k]] == 0)
			{
				dup_pipe(tokens, tree, tree->indexj[k], i);
				exec(tokens, tree, nodes);
			}
			if (tree->indexj[k] > 0)
				close(tree->fdpipe[tree->indexj[k] - 1][0]);
			if (tree->indexj[k] < i)
				close(tree->fdpipe[tree->indexj[k]][1]);
			k++;
		}
		if(nodes->right)
			nodes = nodes->right;
		if(j == tree->indexj[k])
			k++;
		j++;
	}
	j = 0;
	while (j <= i)
	{
		if(checkj(tree->indexj, j))
			parent_process(tree->status, tree->pid[j], 0);
		j++;
	}
}
