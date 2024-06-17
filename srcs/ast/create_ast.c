/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/13 10:05:43 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	with_pipe(t_node **nodes, t_token **tokens, bool *is_redirec,
		t_tree *tree)
{
	if (get_redirection_left(*tokens, *nodes, tree))
		check_left_redirec(nodes, tokens, is_redirec, tree);
	else
		add_node_left(*nodes, tokens, tree);
}

static void	without_pipe(t_token **tokens, t_node *nodes, t_tree *tree)
{
	if (get_redirection_main(*tokens, nodes, tree))
		add_node_left(nodes, tokens, tree);
	else
		add_node(nodes, tokens);
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
	(*tree)->head = nodescp;
	if (tokens->next == NULL)
		return (add_node(nodes, &tokens), (void)0);
	while (tokens != NULL)
	{
		if (get_pipe(tokens, nodes))
			with_pipe(&nodes, &tokens, &is_redirec, *tree);
		else
			without_pipe(&tokens, nodes, *tree);
		add_branches(tokens, &nodes, &nodescp, *tree);
		is_redirec = 1;
	}
	return ((void)0);
}
