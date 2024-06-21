/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:31:56 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/21 14:05:15 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_execve(tokens, tree, node);
}

void	exec(t_token *tokens, t_tree *tree, t_node *node)
{
	if ((is_heredoc(node->left) && !node->left->left) || (is_heredoc(node)
			&& !node->left))
		err_free_all4(tree, tokens);
	if (testredir(node->left) && node->left->left)
	{
		execute_pipe(tokens, tree, node->left->left);
	}
	else if (node->left)
	{
		execute_pipe(tokens, tree, node->left);
	}
	else
		execute_pipe(tokens, tree, node);
}

void	redir_heredoc_in(t_tree *tree)
{
	if (access("./.here_doc", F_OK) != -1)
	{
		tree->fdin = open("./.here_doc", O_RDONLY);
		if (tree->fdin < 0)
			perror("open first");
		if (dup2(tree->fdin, STDIN_FILENO) == -1)
			perror("dup2 first");
	}
}
