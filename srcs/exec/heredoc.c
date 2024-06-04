/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:58 by bastpoy           #+#    #+#             */
/*   Updated: 2024/06/04 11:17:44 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **find_heredoc(t_tree *tree, t_node *nodes) 
{
    char **eofword;
    int i;

    i = 0 ;
    init_eofword(tree, nodes, &eofword);
    while(nodes)
    {
        if(nodes->type == TOKEN_REDIR_HEREDOC) // si jai un heredoc
        {
            if(nodes->right->type != TOKEN_WORD) // si mon token dapres est different d'un word
            {
                if(nodes->right->left && nodes->right->left->type == TOKEN_WORD)
                    get_eofword(tree, eofword, nodes->right->left, &i);
                else
                    err_free_all(tree);
            }
            else // si mon token dapres est un word
                get_eofword(tree, eofword, nodes->right, &i);
        }
        nodes = nodes->right;
    }
    if(i != 0)
        eofword[i] = NULL;
    return (eofword);
}

static void close_heredoc(t_tree *tree, char **eofword)
{
    free_array(eofword);
    close(tree->fdin);
    tree->fdin = open(".here_doc", O_RDONLY);
    if(dup2(tree->fdin, STDIN_FILENO) == -1)
        err_free_all(tree);
    close(tree->fdin);
}

static void text_heredoc(t_tree *tree, char **eofword, char *input, int *i)
{
    if(ft_str_equals(eofword[*i], input))
        *i = *i + 1;
    else
    {
        input = ft_strtrim(input, "\n"); 
        input = expand_string(input, tree->env);
        if(!eofword[*i + 1])
        {
            ft_putstr_fd(input, tree->fdin);
            ft_putchar_fd('\n', tree->fdin);
        }
    }
    free(input);       
}

void heredoc(t_tree *tree, t_node *nodes)
{
    char *input;
    char **eofword;
    int i;

    i = 0;
    eofword = find_heredoc(tree, nodes);
    if(eofword)
    {
        tree->fdin = open(".here_doc",  O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if(tree->fdin < 0)
            err_free_all(tree);
        while(eofword[i])
        {
            ft_putstr_fd("heredoc> ", 0);
            input = get_next_line(0);
            if(signal_status ==  130)
                break;
            if(!input)
                err_null_heredoc(tree, eofword, i);
            text_heredoc(tree, eofword, input, &i);
        }
        close_heredoc(tree, eofword);
    }
}
