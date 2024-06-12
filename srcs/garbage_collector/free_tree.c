/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:14:56 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/12 19:14:18 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pipe(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree->nodes->type == TOKEN_PIPE)
	{
		i++;
		tree->nodes = tree->nodes->right;
	}
	while (i > 0)
	{
		free(tree->fdpipe[i - 1]);
		i--;
	}
	free(tree->fdpipe);
}

static void	free_nodes(t_node *nodes)
{
	int	i;

	i = 0;
	if (nodes == NULL)
		return ;
	free_nodes(nodes->left);
	free_nodes(nodes->right);
	if (nodes->args != NULL)
	{
		while (nodes->args[i])
		{
			free(nodes->args[i]);
			i++;
		}
		free(nodes->args);
	}
	free(nodes);
}

void	free_envp(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree->envp[i])
	{
		free(tree->envp[i]);
		i++;
	}
	free(tree->envp);
}

void	free_tree(t_tree **tree, int env)
{
	t_tree	*treecp;

	treecp = *tree;
	if ((treecp))
	{
		printf("free_tree\n");
		if (treecp->fdpipe)
			free_pipe(treecp);
		if (treecp->nodebegin)
			free_nodes(treecp->nodebegin);
		if (treecp->envp)
			free_envp(treecp);
		if (treecp->env && env == 1)
			free_env(treecp->env);
		treecp->env = NULL;
		treecp->fdpipe = NULL;
		treecp->nodebegin = NULL;
		treecp->nodes = NULL;
		treecp->envp = NULL;
		free(treecp);
		(*tree) = NULL;
	}
}
