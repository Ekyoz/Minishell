/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:08:04 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/18 12:08:59 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	do_heredoc(t_token *tokens, t_tree *tree, int j, int i)
{
	if (j == 0)
	{
		hdoc_or_cmd(tree->nodebegin->left);
		if (!heredoc(tree, tree->nodebegin->left))
			return (free_tree_tokens(&tree, tokens), unlink("./.here_doc"), false);
	}
	else if (j == i)
	{
		hdoc_or_cmd(tree->nodebegin);
		if (!heredoc(tree, tree->nodebegin))
			return (free_tree_tokens(&tree, tokens), unlink("./.here_doc"), false);
	}
	else
	{
		hdoc_or_cmd(tree->nodebegin->left);
		if (!heredoc(tree, tree->nodebegin->left))
			return (free_tree_tokens(&tree, tokens), unlink("./.here_doc"), false);
	}
	return (true);
}
