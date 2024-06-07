/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:29:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/06 18:11:14 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pipe(t_token *token, t_node *nodes)
{
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		token = token->next;
	}
	if (token != NULL && token->type == TOKEN_PIPE)
	{
		nodes->type = TOKEN_PIPE;
		token->type = PIPEUSED;
		nodes->args = token->value;
		return (1);
	}
	else
		return (0);
}

int	get_redirection_left(t_token *token, t_node *nodes, t_tree *tree)
{
	while (token != NULL && token->type != TOKEN_REDIR_IN
		&& token->type != TOKEN_REDIR_OUT && token->type != TOKEN_REDIR_APPEND
		&& token->type != TOKEN_REDIR_HEREDOC && token->type != PIPEUSED)
	{
		token = token->next;
	}
	if (token != NULL && (token->type == TOKEN_REDIR_IN
			|| token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_REDIR_APPEND
			|| token->type == TOKEN_REDIR_HEREDOC))
	{
		nodes->left = init_nodes(tree);
		nodes->left->type = token->type;
		nodes->left->args = token->value;
		token->type = REDIRUSED;
		return (1);
	}
	else
		return (0);
}

int	get_redirection_right(t_token *token, t_node *nodes, t_tree *tree)
{
	while (token != NULL && token->type != TOKEN_REDIR_IN
		&& token->type != TOKEN_REDIR_OUT && token->type != TOKEN_REDIR_APPEND
		&& token->type != TOKEN_REDIR_HEREDOC && token->type != PIPEUSED)
	{
		token = token->next;
	}
	if (token != NULL && (token->type == TOKEN_REDIR_IN
			|| token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_REDIR_APPEND
			|| token->type == TOKEN_REDIR_HEREDOC))
	{
		nodes->right = init_nodes(tree);
		nodes->right->type = token->type;
		nodes->right->args = token->value;
		token->type = REDIRUSED;
		return (1);
	}
	else
		return (0);
}

int	get_redirection_main(t_token *token, t_node *nodes, t_tree *tree)
{
	while (token != NULL && token->type != TOKEN_REDIR_IN
		&& token->type != TOKEN_REDIR_OUT && token->type != TOKEN_REDIR_APPEND
		&& token->type != TOKEN_REDIR_HEREDOC && token->type != PIPEUSED)
	{
		token = token->next;
	}
	if (token != NULL && (token->type == TOKEN_REDIR_IN
			|| token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_REDIR_APPEND
			|| token->type == TOKEN_REDIR_HEREDOC))
	{
		if (!nodes)
			nodes = init_nodes(tree);
		nodes->type = token->type;
		nodes->args = token->value;
		token->type = REDIRUSED;
		return (1);
	}
	else
		return (0);
}
