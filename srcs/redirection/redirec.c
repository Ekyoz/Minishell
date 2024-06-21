/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:52:24 by bastpoy           #+#    #+#             */
/*   Updated: 2024/06/21 16:41:00 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_redir_out(t_token *tokens, t_tree *tree, t_node *nodes,
		int *isredir)
{
	if (nodes->type == TOKEN_REDIR_OUT)
	{
		if (nodes->right->type == TOKEN_REDIR_OUT
			|| nodes->right->type == TOKEN_REDIR_IN
			|| nodes->right->type == TOKEN_REDIR_APPEND
			|| nodes->right->type == TOKEN_REDIR_HEREDOC)
		{
			tree->fdout = open(nodes->right->left->args[0],
					O_TRUNC | O_CREAT | O_WRONLY, 0644);
			if (tree->fdout < 0 && tree->error[0] == 0)
				print_error(tokens, OPEN_FILE_ERR, tree, nodes->right->left);
		}
		else
		{
			tree->fdout = open(nodes->right->args[0],
					O_TRUNC | O_CREAT | O_WRONLY, 0644);
			if (tree->fdout < 0 && tree->error[0] == 0)
			{
				print_error(tokens, OPEN_FILE_ERR, tree, nodes->right);
			}
		}
		*isredir = 1;
	}
}

void	find_redir_in(t_token *tokens, t_tree *tree, t_node *nodes,
		int *isredir)
{
	if (nodes->type == TOKEN_REDIR_IN)
	{
		if (nodes->right->type == TOKEN_REDIR_IN
			|| nodes->right->type == TOKEN_REDIR_OUT
			|| nodes->right->type == TOKEN_REDIR_APPEND
			|| nodes->right->type == TOKEN_REDIR_HEREDOC)
		{
			tree->fdin = open(nodes->right->left->args[0], O_RDONLY, 0644);
			if (tree->fdin < 0 && tree->error[0] == 0)
				print_error(tokens, OPEN_FILE_ERR, tree, nodes->right->left);
		}
		else
		{
			tree->fdin = open(nodes->right->args[0], O_RDONLY, 0644);
			if (tree->fdin < 0 && tree->error[0] == 0)
			{
				print_error(tokens, OPEN_FILE_ERR, tree, nodes->right);
			}
		}
		*isredir = 1;
	}
}

void	find_redir_append(t_token *tokens, t_tree *tree, t_node *nodes,
		int *isredir)
{
	if (nodes->type == TOKEN_REDIR_APPEND)
	{
		if (nodes->right->type == TOKEN_REDIR_OUT
			|| nodes->right->type == TOKEN_REDIR_OUT
			|| nodes->right->type == TOKEN_REDIR_APPEND)
		{
			tree->fdout = open(nodes->right->left->args[0],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (tree->fdout < 0 && tree->error[0] == 0)
				print_error(tokens, OPEN_FILE_ERR, tree, nodes->right->left);
		}
		else
		{
			tree->fdout = open(nodes->right->args[0],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (tree->fdout < 0 && tree->error[0] == 0)
				print_error(tokens, OPEN_FILE_ERR, tree, nodes->right);
		}
		*isredir = 1;
	}
}

int	check_redir_out(t_token *tokens, t_tree *tree, t_node *nodes)
{
	int	isredir;

	isredir = 0;
	while (nodes)
	{
		find_redir_out(tokens, tree, nodes, &isredir);
		find_redir_append(tokens, tree, nodes, &isredir);
		nodes = nodes->right;
	}
	if (isredir == 1)
	{
		tree->fdoutcp = dup(STDOUT_FILENO);
		if (dup2(tree->fdout, STDOUT_FILENO) == -1)
		{
			perror("");
			err_free_all(tree);
		}
		close(tree->fdout);
	}
	return (isredir);
}

int	check_redir_in(t_token *tokens, t_tree *tree, t_node *nodes)
{
	int	isredir;

	isredir = 0;
	while (nodes)
	{
		find_redir_in(tokens, tree, nodes, &isredir);
		nodes = nodes->right;
	}
	if (isredir == 1)
	{
		if (dup2(tree->fdin, STDIN_FILENO) == -1)
			err_free_all(tree);
		close(tree->fdin);
	}
	return (isredir);
}
