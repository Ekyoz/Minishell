/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:08:04 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/17 16:15:12 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	do_heredoc(t_token *tokens, t_tree *tree, int j, int i)
{
	if (j == 0)
	{
		hdoc_or_cmd(tree->nodebegin->left);
		if (!heredoc(tokens, tree, tree->nodebegin->left))
			return (unlink("./.here_doc"), false);
	}
	else if (j == i)
	{
		hdoc_or_cmd(tree->nodebegin);
		if (!heredoc(tokens, tree, tree->nodebegin))
			return (unlink("./.here_doc"), false);
	}
	else
	{
		hdoc_or_cmd(tree->nodebegin->left);
		if (!heredoc(tokens, tree, tree->nodebegin->left))
			return (unlink("./.here_doc"), false);
	}
	return (true);
}
