/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:00:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/11 17:38:19 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(int **fdpipe, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		close(fdpipe[j][0]);
		close(fdpipe[j][1]);
		j++;
	}
}

void	first_pipe(t_token *tokens, t_tree *tree, t_node *node)
{
	if (!check_redir_out(tokens, tree, node) && !testopening(tokens, tree,
			node))
	{
		if (dup2(tree->fdpipe[0][1], STDOUT_FILENO) == -1)
			err_free_all(tree);
	}
	check_redir_in(tokens, tree, node);
	heredoc(tokens, tree, node);
}

void	last_pipe(t_token *tokens, t_tree *tree, t_node *node, int j)
{
	check_redir_out(tokens, tree, node);
	if (!check_redir_in(tokens, tree, node))
	{
		if (dup2(tree->fdpipe[j - 1][0], STDIN_FILENO) == -1)
			err_free_all(tree);
	}
	heredoc(tokens, tree, node);
}

void	mid_pipe(t_token *tokens, t_tree *tree, t_node *node, int j)
{
	if (!check_redir_in(tokens, tree, node))
	{
		if (dup2(tree->fdpipe[j - 1][0], STDIN_FILENO) == -1)
			err_free_all(tree);
	}
	if (!check_redir_out(tokens, tree, node) && check_cmd1(tree, node))
	{
		if (dup2(tree->fdpipe[j][1], STDOUT_FILENO) == -1)
			err_free_all(tree);
	}
	heredoc(tokens, tree, node);
}

void	wait_all_parent(t_tree *tree, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		parent_process(tree->status, tree->pid[j]);
		j++;
	}
}
