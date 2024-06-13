/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:00:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/13 18:15:25 by bpoyet           ###   ########.fr       */
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
	if(is_heredoc(node) && !check_redir_in(tokens, tree, node))
	{
        tree->fdin = open(".heredoc", O_RDONLY);
        if(tree->fdin < 0)
            perror("open");
        if(dup2(tree->fdin, STDIN_FILENO) == -1)
            perror("dup2 first");
        close(tree->fdin);
	}
	if (!check_redir_out(tokens, tree, node) && !testopening(tokens, tree,
			node))
	{
		fprintf(stderr, "je dup out \n");
		if (dup2(tree->fdpipe[0][1], STDOUT_FILENO) == -1)
			err_free_all(tree);
	}
	// check_redir_in(tokens, tree, node);
}

void	last_pipe(t_token *tokens, t_tree *tree, t_node *node, int j)
{
	if(is_heredoc(node) && !check_redir_in(tokens, tree, node))
	{
		if(dup2(tree->fdin, tree->fdincp) == -1)
			perror("dup2 last");
		close(tree->fdin);
	}
	check_redir_out(tokens, tree, node);
	if (!check_redir_in(tokens, tree, node) && !is_heredoc(node))
	{
		fprintf(stderr, "je dup in\n");
		if (dup2(tree->fdpipe[j - 1][0], STDIN_FILENO) == -1)
			err_free_all(tree);
	}
}	

void	mid_pipe(t_token *tokens, t_tree *tree, t_node *node, int j)
{
	if(is_heredoc(node))
	{
		tree->fdincp = dup(STDIN_FILENO);
		if(dup2(tree->fdin, tree->fdincp) == -1)
			perror("dup2 mid");
		close(tree->fdin);
	}
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
}

void	wait_all_parent(t_tree *tree, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		parent_process(tree, tree->status, tree->pid[j]);
		j++;
	}
}
