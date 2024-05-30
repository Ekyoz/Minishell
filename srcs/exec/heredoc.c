/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:58 by bastpoy           #+#    #+#             */
/*   Updated: 2024/05/29 15:12:27 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_eofword(t_tree *tree, t_node *nodes, char ***eofword) // fonction qui init tous les eof
{
    int i;

    i = 0;
    while(nodes)
    {
        if(nodes->type == TOKEN_REDIR_HEREDOC)
            i++;
        nodes = nodes->right;
    }
    if(i > 0)
    {
        *eofword = (char **)malloc(sizeof(char *) * (i + 1));
        if(!(*eofword))
            err_free_all(tree);
    }
    else
        *eofword = NULL;
}

//je trouve les heredoc et je retourne tous les eof dans un char**
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
                printf("le node de droite %d\n", nodes->right->type);
                if(nodes->right->left && nodes->right->left->type == TOKEN_WORD)
                {
                    eofword[i] = ft_strdup(nodes->right->left->args[0]);
                    if(!eofword[i])
                        err_free_all(tree);
                    fprintf(stderr, "eof %s\n", eofword[i]);
                    i++;
                }
                else
                {
                    ft_putstr_fd("error errdoc\n", 2);
                    return(NULL);
                }
            }
            else // si mon token dapres est un word
            {
                eofword[i] = ft_strdup(nodes->right->args[0]);
                if(!eofword[i])
                    err_free_all(tree);
                fprintf(stderr, "eof %s\n", eofword[i]);
                i++;
            }
        }
        nodes = nodes->right;
    }
    if(i != 0)
        eofword[i] = NULL;
    return (eofword);
}

bool is_heredoc(t_node *nodes)
{
    if(nodes)
    {
        while(nodes)
        {
            if(nodes->type == TOKEN_REDIR_HEREDOC)
                return(1);
            nodes = nodes->right;
        }
    }
    return(0);
}

void heredoc(t_tree *tree, t_node *nodes)
{
    char *input;
    char **eofword;

    eofword = find_heredoc(tree, nodes);
    if(eofword)
    {
        tree->fdin = open(".here_doc",  O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if(tree->fdin < 0)
            perror("error opening");
        while(*eofword)
        {
            input = readline("> ");
            if(!input)
            {
                printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", *eofword);
                exit(0);
            }
            write(tree->fdin, input, ft_strlen(input));
            write(tree->fdin, "\n", 1);
            if(!ft_strcmp(*eofword, input))
                eofword++;
        }
        close(tree->fdin);
        tree->fdin = open(".here_doc", O_RDONLY);
        if(dup2(tree->fdin, STDIN_FILENO) == -1)
            err_free_all(tree);
        close(tree->fdin);
    }
}
