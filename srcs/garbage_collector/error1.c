/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:35:12 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/21 16:19:58 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_free_all1(t_tree *tree, t_token *tokens)
{
	free_tree_tokens(&tree, tokens);
	exit(0);
}

void	err_free_all2(t_tree *tree, t_token *tokens)
{
	perror("");
	free_tree_tokens_env(&tree, tokens);
	exit(errno);
}

void	err_free_all3(t_tree *tree, t_token *tokens, t_node *node, char **tmp)
{
	if (errno == 13)
		g_signal_status = 126;
	if (errno == 2)
		g_signal_status = 127;
	if (node->args && node->args[0])
		perror(node->args[0]);
	else
		perror("");
	free_array(&tmp);
	free_tree_tokens_env(&tree, tokens);
	exit(g_signal_status);
}

void	err_free_all4(t_tree *tree, t_token *tokens)
{
	free_tree_tokens_env(&tree, tokens);
	exit(0);
}
