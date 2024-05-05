/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:58 by bastpoy           #+#    #+#             */
/*   Updated: 2024/05/05 17:58:10 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_eofword(t_node *nodes, char ***eofword)// fonction qui init tous les eof
{
    int i;

    i = 0;
    while(nodes)
    {
        if(nodes->type == TOKEN_REDIR_HEREDOC)
            i++;
        nodes = nodes->right;
    }
    fprintf(stderr, "i vaut %d\n", i);
    if(i > 0)
        *eofword = (char **)malloc(sizeof(char *) * (i + 1));
        //proteger le malloc
    else
        *eofword = NULL;
}

//je trouve les heredoc et je retourne tous les eof dans un char**
char **find_heredoc(t_node *nodes) 
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
                    fprintf(stderr, "eof %s\n", eofword[i]);
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
                eofword[i] = ft_strdup(nodes->right->args[0]);
                fprintf(stderr, "eof %s\n", eofword[i]);
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
    if(i != 0)
        eofword[i] = NULL;
    return (eofword);
}

void heredoc(t_tree *tree, t_node *nodes)
{
    char *input;
    char **eofword;

    eofword = find_heredoc(nodes);
    if(eofword)
    {
        tree->fdin = open(".here_doc",  O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if(tree->fdin < 0)
            perror("error opening");
        fprintf(stderr, "dans la boucle\n");
        while(*eofword)
        {
            input = readline("> ");
            write(tree->fdin, input, ft_strlen(input));
            write(tree->fdin, "\n", 1);
            if(!ft_strcmp(*eofword, input))
                eofword++;
        }
        close(tree->fdin);
        tree->fdin = open(".here_doc", O_RDONLY);
        dup2(tree->fdin, STDIN_FILENO);
        close(tree->fdin);
    }
}
