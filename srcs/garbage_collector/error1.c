/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:35:12 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/18 16:22:50 by bpoyet           ###   ########.fr       */
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
	free_tree_tokens_env(&tree, tokens);
	exit(0);
}
