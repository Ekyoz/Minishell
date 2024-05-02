/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:58 by bastpoy           #+#    #+#             */
/*   Updated: 2024/05/02 23:26:02 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_eofword(t_node *nodes, char ***eofword)
{
    int i;

    i = 0;
    while(nodes)
    {
        if(nodes->type == TOKEN_REDIR_HEREDOC)
            i++;
        nodes = nodes->right;
    }
    *eofword = (char **)malloc(sizeof(char *) * (i + 1));
    //proteger le malloc
    
}

static char **find_heredoc(t_tree *tree, t_node *nodes)
{
    char **eofword;

    int i;

    i = 0 ;

    init_eofword(nodes, &eofword);
    while(nodes)
    {
        if(nodes->type == TOKEN_REDIR_HEREDOC) // si jai un heredoc
        {
            if(nodes->right->type != TOKEN_WORD) // si mon token dapres est different d'un word
            {
                if(nodes->right->left->type == TOKEN_WORD)
                {
                    eofword[i] = ft_strdup(nodes->right->left->args[0]);
                    i++;
                }
                else
                {
                    printf("error errdoc\n");
                    return(NULL);
                }
            }
            else if(nodes->right->type == TOKEN_WORD) // si mon token dapres est un word
            {
                eofword[i] = ft_strdup(nodes->right->left->args[0]);
                i++;
            }
            else // sinon je n'ai pas d'eof donc erreur
            {
                printf("pas de eof apres le heredoc");
                return(NULL);
            }
        }
        nodes = nodes->right;
    }
    return (eofword);
}

void heredoc(t_tree *tree, t_node *nodes)
{
    // si j'ai un redir out
    int fd;

    fd = 0;
    if(check_redir_out(tree, nodes))
    {
        fd = tree->fdout; //je redirige pour ecrire mon heredoc dans un fichier
    }
    if(!find_heredoc(tree, nodes))
    {

    }
    else// il faut que je lise tant que j'ai pas tous les eof de finis
    {
        // readline();
    }
}
