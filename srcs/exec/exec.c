/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/17 16:37:29 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_token(t_token *tokens)
{
    // exemple avec cat -e input > output > output 1 | echo re
    t_token *tokencp;

    tokencp = tokens;

    printf("cat -e input > output > output 1 | echo re\n");
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

void print_command(char **command)
{
    int i = 0;

    while(command[i])
    {
        printf("%s ", command[i]);
        i++;
    }
}

void get_print_branch(t_node *node)
{
    if(node->left)
    {
        printf("%d\n", node->left->file_type);
        if(node->right)
        {
            printf("%d\n", node->right->file_type);
            get_print_branch(node->right);
        }
    }
}

void print_tree(t_node *node)
{
    while(node != NULL)
    {
        printf("%d\n", node->file_type);
        if(node->left)
            get_print_branch(node);
        node = node->right;
    }
}

void create_node(t_token *tokens, t_node **nodesbegin)
{
    t_node *nodes;
    t_node *nodescp; // copie de node qui va contenir l'addresse de la branche right du potentiel prochain pipe
    t_token *tokencp;
    bool is_pipe; // boolean a 1 si un pipe est sur ma branche
	bool is_redirec; // boolean a 1 si une redirec est sur ma branche

    is_pipe = 0;
    is_redirec = 1;
    tokencp = tokens;
    nodes = init_nodes();
    nodescp = nodes; // une recopie pour stocker le premier node
    *nodesbegin = nodescp;
    if(!nodes)
        return((void) 0);
    if(tokencp->next == NULL)
    {
        // j'appelle une fonction qui execute seulement une commande
        printf("j'execute une commande\n");
        return((void) 0);
    }
    while(tokencp != NULL)
    {
        // Je stocke dans ma liste les pipe en premier
        if(get_pipe(tokencp, nodes))
        {
            is_pipe = 1; // je mets la variable a 1 pour dire que jai bien trouve un pipe
            // il faut aussi que je stocke l'adresse du right pour reprendre a son adresse 
            printf("Commande pipe\n"); 
        }
        // Ensuite je stocke les redirections
        if(is_pipe == 1)
        {
            // tant que j'ai des redirections sur la branche de gauche
            // ma premiere redirection passe a gauche
            if(get_redirection_left(tokencp, nodes)) 
            {
                printf("Redirection a gauche\n");
                while(is_redirec == 1)
                {
                    nodes->left->type = tokens->type; // a gauche de la redirec c'est forcement une commande
                    nodes->left->args = ft_split(tokens->value, ' '); // je stocke la commande
                    tokens = tokens->next->next; // je saute la redirection donc deux next
                    tokencp = tokens; // je reavance le curseur de ma copie
                    printf("commande a gauche :");
                    print_command(nodes->left->args);
                    printf("\n"); 
                    // mes autres redirections a droite si j'ai d'autres redirections
                    if(get_redirection_right(tokencp, nodes)) // je regarde a droite si j'ai une redirection
                    {
                        printf("Une redirection a droite\n");
                        is_redirec = 1;
                    }
                    else
                    {
                        // pas d'autres redirections donc c'est une commande
                        // il faut que j'arrive a recuperer la bonne commande
                        printf("Commande a droite : ");
                        nodes->right->type = tokens->type;
                        nodes->right->args = ft_split(tokens->value, ' ');
                        tokens = tokens->next->next; // je saute la redirection donc deux next
                        tokencp = tokens; // je reavance le curseur de ma copie
                        is_redirec = 0;
                        print_command(nodes->right->args);
                        printf("\n");
                    }
                }
            } 
            else // je fais une commande a gauche
            {
                nodes->left = init_nodes(nodes);
                nodes->left->type = tokens->type;
                nodes->left->args = ft_split(tokens->value, ' ');
                tokens = tokens->next; // Je passe au prochain token
                tokencp = tokens; // je reavance le curseur de ma copie
                is_redirec = 0;
                printf("commande a gauche: ");
                print_command(nodes->left->args);
                printf("\n");
            }
        }
        else
        {
            printf("dans pas de pipe\n");
            // CONDITION pas de pipe je verifie si j'ai une redirection
            if(get_redirection_main(tokencp, nodes))
            {
                // si j'ai une redirection je stocke la commande de gauche
                nodes->left = init_nodes(nodes);
                nodes->left->type = tokens->type;
                nodes->left->args = ft_split(tokens->value, ' ');
                tokens = tokens->next; // Je passe au prochain token
                tokencp = tokens; // je reavance le curseur de ma copie
                is_redirec = 0;
                printf("commande a gauche :");
                print_command(nodes->left->args);
                printf("\n");                
            }
            // si j'en ai pas j'effectnodesue une commande
            else
            {
                nodes = init_nodes(nodes);
                nodes->type = tokens->type;
                nodes->args = ft_split(tokens->value, ' ');
                tokens = tokens->next; // Je passe au prochain token
                tokencp = tokens; // je reavance le curseur de ma copie
                is_redirec = 0;
                printf("commande: ");
                print_command(nodes->args);
                printf("\n"); 
            }
        }
        is_pipe = 0; 
        is_redirec = 1;
        // apres avoir etabli la branche de gauche je malloc la branche de droite
        // je me replace a l'adresse de la branche de droite dans mon nodes
        nodescp->right = init_nodes(nodescp);
        nodescp = nodescp->right;
        nodes = nodescp;
    }
    return((void) 0);
}

int main()
{
    t_token *tokens;
    t_node *nodes;

    tokens = (t_token *)malloc(sizeof(t_token));
    t_token *tokenscp = tokens;
    nodes = init_nodes();
    printf("tokens %p\n", tokens);
    tokens = ft_token(tokens);
    printf("tokens %p\n", tokens);
    while(tokens != NULL)
    {
        printf("value %s\n", tokens->value);
        tokens = tokens->next;
    }
    create_node(tokenscp, &nodes);
    printf("\n\n\nJe print tous les nodes\n\n");
    print_tree(nodes);
    return (0);
}

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