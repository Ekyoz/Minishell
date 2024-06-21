/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:00:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/21 13:33:47 by bastpoy          ###   ########.fr       */
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
	if (is_heredoc(node))
	{
		tree->fdin = open("./.here_doc", O_RDONLY);
		if (tree->fdin < 0)
			perror("open first");
		if (dup2(tree->fdin, STDIN_FILENO) == -1)
			perror("dup2 first");
	}
	if (!check_redir_out(tokens, tree, node))
	{
		if (dup2(tree->fdpipe[0][1], STDOUT_FILENO) == -1)
			err_free_all(tree);
	}
	check_redir_in(tokens, tree, node);
}

void	last_pipe(t_token *tokens, t_tree *tree, t_node *node, int j)
{
	if (is_heredoc(node))
	{
		tree->fdin = open("./.here_doc", O_RDONLY);
		if (tree->fdin < 0)
			perror("open");
		if (dup2(tree->fdin, STDIN_FILENO) == -1)
			perror("dup2");
		close(tree->fdin);
	}
	check_redir_out(tokens, tree, node);
	if (!check_redir_in(tokens, tree, node) && !is_heredoc(node))
	{
		if (dup2(tree->fdpipe[j - 1][0], STDIN_FILENO) == -1)
			err_free_all(tree);
	}
}

void	mid_pipe(t_token *tokens, t_tree *tree, t_node *node, int j)
{
	if (access("./.here_doc", F_OK) != -1)
	{
		tree->fdin = open(".here_doc", O_RDONLY);
		if (tree->fdin < 0)
			perror("open");
		if (dup2(tree->fdin, STDIN_FILENO) == -1)
			perror("dup2");
		close(tree->fdin);
	}
	if (!check_redir_in(tokens, tree, node) && !is_heredoc(node))
	{
		if (dup2(tree->fdpipe[j - 1][0], STDIN_FILENO) == -1)
			err_free_all(tree);
	}
	if (!check_redir_out(tokens, tree, node))
	{
		if (dup2(tree->fdpipe[j][1], STDOUT_FILENO) == -1)
			err_free_all(tree);
	}
}

void	wait_all_parent(t_tree *tree, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		parent_process(tree->status, tree->pid[j], 0);
		j++;
	}
	if (access("./.here_doc", F_OK) != -1)
		unlink("./.here_doc");
}
