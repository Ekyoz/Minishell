/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:58:33 by bastpoy           #+#    #+#             */
/*   Updated: 2024/06/06 17:56:23 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_equals(const char *str1, const char *str2)
{
	size_t	index;

	if (!str1 || !str2)
		return (0);
	index = 0;
	while (str1[index] && str2[index])
	{
		if (str1[index] != str2[index])
			return (0);
		index++;
	}
	if (str1[index] != str2[index] && str2[index] != '\n')
		return (0);
	return (1);
}

bool	is_heredoc(t_node *nodes)
{
	if (nodes)
	{
		while (nodes)
		{
			if (nodes->type == TOKEN_REDIR_HEREDOC)
				return (1);
			nodes = nodes->right;
		}
	}
	return (0);
}

void	init_eofword(t_tree *tree, t_node *nodes, char ***eofword)
{
	int	i;

	i = 0;
	while (nodes)
	{
		if (nodes->type == TOKEN_REDIR_HEREDOC)
			i++;
		nodes = nodes->right;
	}
	if (i > 0)
	{
		*eofword = (char **)malloc(sizeof(char *) * (i + 1));
		if (!(*eofword))
			err_free_all(tree);
	}
	else
		*eofword = NULL;
}

void	expand_heredoc(t_tree *tree, t_node *node)
{
	if (node->args)
		tree->expandheredoc = 1;
	else
		tree->expandheredoc = 0;
}

void	get_eofword(t_tree *tree, char **eofword, t_node *node, int *i)
{
	eofword[*i] = ft_strdup(node->args[0]);
	if (!eofword[*i])
		err_free_all(tree);
	*i = *i + 1;
}
