/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:30:32 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/06 19:00:39 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_array1(char **ptr)
{
    int i;
    
    i = 0;
	if (ptr)
	{
		while(ptr[i])
		{
			printf("freeing %p et %s\n", ptr[i], ptr[i]);
			free(ptr[i]);
			i++;
		}
		printf("freeing %p\n", ptr);
		free(ptr);
		ptr = NULL;
	}
}

t_node	*add_node_left(t_node *nodes, t_token **token, t_tree *tree)
{
	if ((*token)->type != REDIRUSED)
	{
		nodes->left = init_nodes(tree);
		if((*token)->value)
			printf("token %p\n", (*token)->value[0]);
		nodes->left->type = (*token)->type;
		nodes->left->args = ft_arrdup((*token)->value);
		free_array1((*token)->value);
	}
	*token = (*token)->next;
	if ((*token) != NULL && ((*token)->type == PIPEUSED
			|| (*token)->type == REDIRUSED))
		(*token) = (*token)->next;
	return (nodes);
}

t_node	*add_node_right(t_node *nodes, t_token **token, bool *is_redirec,
		t_tree *tree)
{
	nodes->right = init_nodes(tree);
	nodes->right->type = (*token)->type;
	if((*token)->value)
		printf("token %p\n", (*token)->value[0]);
	nodes->right->args = ft_arrdup((*token)->value);
	free_array1((*token)->value);
	*token = (*token)->next;
	if ((*token) != NULL && ((*token)->type == PIPEUSED
			|| (*token)->type == REDIRUSED))
		(*token) = (*token)->next;
	*is_redirec = 0;
	return (nodes);
}

t_node	*add_node(t_node *nodes, t_token **token)
{
	nodes->type = (*token)->type;
	nodes->args = ft_arrdup((*token)->value);
	if((*token)->value)
		printf("token %p\n", (*token)->value[0]);
	free_array1((*token)->value);
	*token = (*token)->next;
	if ((*token) != NULL && ((*token)->type == PIPEUSED
			|| (*token)->type == REDIRUSED))
		(*token) = (*token)->next;
	return (nodes);
}

t_node	*init_nodes(t_tree *tree)
{
	t_node	*nodes;

	nodes = (t_node *)malloc(sizeof(t_node));
	if (!nodes)
		err_free_all(tree);
	nodes->type = TOKEN_WORD;
	nodes->file_type = 0;
	nodes->tree_level = 0;
	nodes->args = NULL;
	nodes->left = NULL;
	nodes->right = NULL;
	return (nodes);
}

void	add_branches(t_token *tokens, t_node **node, t_node **nodecp,
		t_tree *tree)
{
	if (tokens != NULL)
	{
		(*nodecp)->right = init_nodes(tree);
		(*nodecp) = (*nodecp)->right;
		*node = *nodecp;
	}
}
