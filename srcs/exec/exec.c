/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/16 13:31:10 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token *ft_token(t_token *tokens)
{
    t_token *tokencp;

    tokencp = tokens;

    tokens->type = TOKEN_WORD;
    tokens->value = ft_strdup("cat -e input");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_REDIR_OUT;
    tokens->value = NULL;
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_WORD;
    tokens->value = ft_strdup("output");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_REDIR_OUT;
    tokens->value = NULL;
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_WORD;
    tokens->value = ft_strdup("output1");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_PIPE;
    tokens->value = NULL;
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_WORD;
    tokens->value = ft_strdup("echo re");
    tokens->next = NULL;

    return(tokencp);
}

void create_node(t_token *tokens)
{
    t_node *nodes;
    t_node *nodescp; // copie de node qui va contenir l'addresse de la branche right du potentiel prochain pipe
    t_token *tokencp;
    bool				is_pipe; // boolean a 1 si un pipe est sur ma branche
	bool				is_redirec; // boolean a 1 si une redirec est sur ma branche

    is_pipe = 0;
    is_redirec = 0;
    tokencp = tokens;
    nodes = init_nodes(nodes);
    nodescp = nodes; // une recopie pour stocker le premier node
    if(!nodes)
        return((void) 0);
    if(tokens->next == NULL)
    {
        // j'appelle une fonction qui execute seulement une commande
    }
    while(tokencp->next != NULL)
    {
        // Je stocke dans ma liste les pipe en premier
        // Il faut que je check si c'est bien le premier pipe
        // Si ca l'est pas je le stocke dans la branche de droite

        if(get_pipe(tokencp, nodes))
        {
            is_pipe = 1; // je mets la variable a 1 pour dire que jai bien trouve un pipe
            // il faut aussi que je stocke l'adresse du right pour reprendre a son adresse 
            
            printf("j'ai bien un pipe\n"); 
        }
        // Ensuite je stocke les redirections
        if(is_pipe == 1)
        {
            // tant que j'ai des redirections sur la branche de gauche
            is_redirec == 1;
                // ma premiere redirection passe a gauche
            if(get_redirection_left(tokencp, nodes)) 
            {
                while(is_redirec == 1)
                {
                    nodes->left->type = tokens->type; // a gauche de la redirec c'est forcement une commande
                    nodes->left->args = ft_split(tokens->value, ' '); // je stocke la commande
                    tokens = tokens->next->next; // je saute la redirection donc deux next
                    tokencp = tokens; // je reavance le curseur de ma copie
                    // mes autres redirections a droite si j'ai d'autres redirections
                    if(get_redirection_right(tokencp, nodes)) // je regarde a droite si j'ai une redirection
                    {
                        is_redirec = 1;
                    }
                    else
                    {
                        // pas d'autres redirections donc c'est une commande
                        // il faut que j'arrive a recuperer la bonne commande
                        nodes->right->type = tokens->type;
                        nodes->left->args = ft_split(tokens->value, ' ');
                        tokens = tokens->next->next; // je saute la redirection donc deux next
                        tokencp = tokens; // je reavance le curseur de ma copie
                        is_redirec = 0;
                    }
                }
            } 
            else // jeffectue une commande
            {
                nodes->left = init_nodes(nodes);
                nodes->left->type = tokens->type;
                nodes->left->args = ft_split(tokens->value, ' ');
                tokens = tokens->next->next; // je saute la redirection donc deux next
                tokencp = tokens; // je reavance le curseur de ma copie
                is_redirec = 0;
            }
        }
        else
        {
            // si j'ai pas de pipe je crois que ca revient au meme quand meme
        }
        is_pipe = 0;
        is_redirec = 1;
        // apres avoir etabli la branche de gauche je malloc la branche de droite
        // je me replace a l'adresse de la branche de droite dans mon nodes
        nodescp->right = init_nodes(nodescp);
        nodescp = nodescp->right;
        nodes = nodescp;
    }
}

int main()
{
    // char *input;

    // exec();
    // while (true)
    // {
    //     input = readline("Minishell >");
    //     add_history(input);
    //     change_directory(input);
    //     if(!ft_strncmp(input, "exit", 5))
    //         break;
    // }
    t_token *tokens;

    tokens = (t_token *)malloc(sizeof(t_token));
    printf("tokens %p\n", tokens);
    tokens = ft_token(tokens);
    // printf("tokens %p\n", tokens);
    while(tokens != NULL)
    {
        printf("value %s\n", tokens->value);
        tokens = tokens->next;
    }
    // create_node(tokens);
    return (0);
}
