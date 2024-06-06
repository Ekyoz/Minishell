/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/06 18:44:15 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_print_branch(t_node *node)
{
	printf("Actuelle gauche %d\n", node->type);
	if (node->args)
		printf("l'args vaut %s\n", node->args[0]);
	if (node->left)
	{
		printf("left %d\n", node->left->type);
		if (node->right)
		{
			printf("right %d\n", node->right->type);
			get_print_branch(node->right);
		}
	}
}

void	print_tree(t_node *node)
{
	while (node != NULL)
	{
		printf("premier ou droite %d\n", node->type);
		if (node->args)
			printf("l'args vaut %s\n", node->args[0]);
		if (node->left)
			get_print_branch(node->left);
		node = node->right;
	}
	printf("\n\n");
}

static void	check_left_redirec(t_node **nodes, t_token **token,
		bool *is_redirec, t_tree *tree)
{
	*nodes = (*nodes)->left;
	while (*is_redirec == 1)
	{
		add_node_left(*nodes, token, tree);
		if (get_redirection_right(*token, *nodes, tree))
			*nodes = (*nodes)->right;
		else
			add_node_right(*nodes, token, is_redirec, tree);
	}
}

void	create_node(t_token *tokens, t_tree **tree)
{
	t_node	*nodes;
	t_node	*nodescp;
	bool	is_redirec;

	is_redirec = 1;
	nodes = init_nodes(*tree);
	if (!nodes)
		return ((void)1);
	nodescp = nodes;
	(*tree)->nodes = nodescp;
	(*tree)->nodebegin = nodescp;
	if (tokens->next == NULL)
		return (add_node(nodes, &tokens), (void)0);
	while (tokens != NULL)
	{
		if (get_pipe(tokens, nodes))
		{
			if (get_redirection_left(tokens, nodes, *tree))
				check_left_redirec(&nodes, &tokens, &is_redirec, *tree);
			else
				add_node_left(nodes, &tokens, *tree);
		}
		else
		{
			if (get_redirection_main(tokens, nodes, *tree))
				add_node_left(nodes, &tokens, *tree);
			else
				add_node(nodes, &tokens);
		}
		add_branches(tokens, &nodes, &nodescp, *tree);
		is_redirec = 1;
	}
	return ((void)0);
}
