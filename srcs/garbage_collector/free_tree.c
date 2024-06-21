/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:14:56 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/21 14:12:45 by bastpoy          ###   ########.fr       */
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

static void	free_int(int *array)
{
	free(array);
	array = NULL;
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
		if (treecp->fdpipe)
			free_pipe(treecp);
		if (treecp->head)
			free_nodes(treecp->head);
		if (treecp->envp)
			free_envp(treecp);
		if (treecp->env && env == 1)
			free_env(treecp->env);
		if (treecp->indexj)
			free_int(treecp->indexj);
		treecp->env = NULL;
		treecp->fdpipe = NULL;
		treecp->head = NULL;
		treecp->nodes = NULL;
		treecp->envp = NULL;
		free(treecp);
		(*tree) = NULL;
	}
}
