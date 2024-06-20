/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:43:01 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/20 11:29:22 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	command_nf(t_tree *tree, t_node *node)
{
	if (tree->fdin != -1)
		close(tree->fdin);
	if (tree->fdout != -1)
	{
		if (dup2(tree->fdoutcp, STDOUT_FILENO) == -1)
			err_free_all(tree);
		close(tree->fdoutcp);
	}
	ft_putstr_fd(node->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	print_error(t_token *tokens, int errorcode, t_tree *tree, t_node *node)
{
	if (errorcode == OPEN_FILE_ERR)
	{
		tree->error[0] = 1;
		perror(node->args[0]);
		free_tree_tokens_env(&tree, tokens);
		exit(1);
	}
	if (errorcode == CMD_NOT_FOUND)
	{
		command_nf(tree, node);
	}
	if (tree != NULL)
	{
		if (tree->fdout != -1)
			close(tree->fdout);
		if (tree->fdoutcp != -1)
			close(tree->fdoutcp);
		free_tree(&tree, 1);
		clear_token(&tokens);
	}
	exit(errorcode);
}

void	err_free_all(t_tree *tree)
{
	free_tree(&tree, 1);
	g_signal_status = 1;
	exit(1);
}

void	malloc_tree_err(t_env *env)
{
	free_env(env);
	g_signal_status = 1;
	exit(1);
}

int	command_not_found(t_tree *tree, char *cmd)
{
	(void)tree;
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	g_signal_status = 1;
	return (1);
}
