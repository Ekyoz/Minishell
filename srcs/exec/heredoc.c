/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:58 by bastpoy           #+#    #+#             */
/*   Updated: 2024/06/11 19:45:00 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	last_index(char **eofword, int i)
{
	if (i != 0)
	{
		eofword[i] = NULL;
	}
}

static char	**find_heredoc(t_tree *tree, t_node *nodes)
{
	char	**eofword;
	int		i;

	i = 0;
	init_eofword(tree, nodes, &eofword);
	while (nodes)
	{
		if (nodes->type == TOKEN_REDIR_HEREDOC)
		{
			expand_heredoc(tree, nodes);
			if (nodes->right->type != TOKEN_WORD)
			{
				if (nodes->right->left
					&& nodes->right->left->type == TOKEN_WORD)
					get_eofword(tree, eofword, nodes->right->left, &i);
				else
					err_free_all(tree);
			}
			else
				get_eofword(tree, eofword, nodes->right, &i);
		}
		nodes = nodes->right;
	}
	last_index(eofword, i);
	return (eofword);
}

static void	close_heredoc(t_token *tokens, t_tree *tree, char **eofword)
{
	free_array(&eofword);
	close(tree->fdin);
	if (g_signal_status == 130)
	{
		free_tree(&tree, 1);
		clear_token(&tokens);
		exit(g_signal_status);
	}
	tree->fdin = open(".here_doc", O_RDONLY);
	if (tree->fdin < 0)
		perror("open 2");	
	if (dup2(tree->fdin, STDIN_FILENO) == -1)
	{
		perror("dup2");
		err_free_all(tree);
	}
	close(tree->fdin);
}

static void	text_heredoc(t_tree *tree, char **eofword, char *input, int *i)
{
	char *temp;
	if (ft_str_equals(eofword[*i], input))
		*i = *i + 1;
	else
	{
		if(ft_strncmp(input, "\n", 2))
		{
			temp = input;
			input = ft_strtrim(input, "\n");
			free(temp);
		}
		if (tree->expandheredoc == 1)
			input = expand_string(input, tree->env);
		if (!eofword[*i + 1])
		{
			ft_putstr_fd(input, tree->fdin);
			ft_putchar_fd('\n', tree->fdin);
		}
	}
	free(input);
}

void	heredoc(t_token *tokens, t_tree *tree, t_node *nodes)
{
	char	*input;
	char	**eofword;
	int		i;

	i = 0;
	eofword = find_heredoc(tree, nodes);
	if (eofword)
	{
		tree->fdin = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if(tree->fdin < 0)
			perror("open");
		fprintf(stderr, "eofword[0] = %s\n", eofword[0]);
		if (tree->fdin < 0)
			err_free_all(tree);
		while (eofword[i])
		{
			g_signal_status = 0;
			ft_putstr_fd("heredoc> ", 0);
			input = get_next_line(0);
			if (g_signal_status == 130)
				break ;
			if (!input)
				err_null_heredoc(tokens, tree, eofword, &i);
			text_heredoc(tree, eofword, input, &i);
		}
		close_heredoc(tokens, tree, eofword);
	}
}
