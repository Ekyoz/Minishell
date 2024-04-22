/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/21 19:06:27 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_string(char *string)
{
    char **output = ft_split(string, ' ');
    return(output);
}
void print_token(t_token * tokens)
{
    while(tokens != NULL)
    {
        if(tokens->value)
            printf("token %s -", tokens->value[0]);
        tokens = tokens->next;
    }
    printf("\n");
}

t_token *ft_token(t_token *tokens)
{
    // exemple avec cat -e input > output > output 1 | echo re
    // t_token *tokencp;

    // tokencp = tokens;

    printf("cat -e input > output > output1 | echo re > outfile > outfile1\n");
    tokens->type = TOKEN_WORD;
    tokens->value = create_string("cat -e input");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_REDIR_OUT;
    tokens->value = create_string("redirecout");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_WORD;
    tokens->value = create_string("output");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_REDIR_OUT;
    tokens->value = create_string("redirecout1");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_WORD;
    tokens->value = create_string("output1");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_PIPE;
    tokens->value = create_string("pipe");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_WORD;
    tokens->value = create_string("echo re");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_REDIR_OUT;
    tokens->value = create_string("redirecout2");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_WORD;
    tokens->value = create_string("outfile");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_REDIR_OUT;
    tokens->value = create_string("redirecou3");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    tokens->type = TOKEN_WORD;
    tokens->value = create_string("outfile1");
    tokens->next = (t_token *)malloc(sizeof(t_token));
    tokens = tokens->next;

    return tokens;
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
    if(node->args)
        printf("Actuelle gauche %s\n", node->args[0]);
    if(node->left)
    {
        if(node->left->args)
        printf("left %s\n", node->left->args[0]);
        if(node->right)
        {
            if(node->right->args)
            printf("right %s\n", node->right->args[0]);
            get_print_branch(node->right);
        }
    }
}

void print_tree(t_node *node)
{
    while(node != NULL)
    {
        if(node->args)
            printf("premier ou droite %s\n", node->args[0]);
        if(node->left)
            get_print_branch(node->left);
        node = node->right;
    }
}

void create_node(t_token *tokens, t_node **nodesbegin)
{
    t_node *nodes;
    t_node *nodescp; // copie de node qui va contenir l'addresse de la branche right du potentiel prochain pipe
    t_token *tokencp;
	bool is_redirec; // boolean a 1 si une redirec est sur ma branche

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
        return((void) 0);
    }
    while(tokencp != NULL)
    {
        // Je stocke dans ma liste les pipe en premier
        if(get_pipe(tokencp, nodes))
        // Ensuite je stocke les redirections
        {
            // tant que j'ai des redirections sur la branche de gauche
            // ma premiere redirection passe a gauche
            if(get_redirection_left(tokencp, nodes)) 
            {
                nodes = nodes->left;// je suis sur la redirection
                while(is_redirec == 1)
                { 
                    add_node_left(nodes, tokens);
                    tokens = tokens->next->next; // je saute la redirection donc deux next
                    tokencp = tokens; // je reavance le curseur de ma copie
                    if(get_redirection_right(tokencp, nodes)) // je regarde a droite si j'ai une redirection
                    {
                        nodes = nodes->right; // decalle branche de droite    
                        is_redirec = 1;
                    }
                    else
                    {
                        // pas d'autres redirections donc c'est une commande
                        // il faut que j'arrive a recuperer la bonne commande
                        add_node_right(nodes, tokens);
                        tokens = tokens->next->next; // je saute la redirection donc deux next
                        tokencp = tokens; // je reavance le curseur de ma copie
                        is_redirec = 0;
                    }
                }
            } 
            else // je fais une commande a gauche
            {
                add_node_left(nodes, tokens);
                tokens = tokens->next; // Je passe au prochain token
                tokencp = tokens; // je reavance le curseur de ma copie
                is_redirec = 0;
            }
        }
        else
        {
            // CONDITION pas de pipe je verifie si j'ai une redirection
            if(get_redirection_main(tokencp, nodes))
            {
                // si j'ai une redirection je stocke la commande de gauche
                add_node_left(nodes, tokens);
                tokens = tokens->next->next; // Je passe au prochain token
                printf("dans la redirection main\n");
                print_token(tokens);
                tokencp = tokens; // je reavance le curseur de ma copie
            }
            // si j'en ai pas j'effectnodesue une commande
            else
            {
                add_node(nodes, tokens);
                tokens = tokens->next; // Je passe au prochain token
                printf("Pas de redirection\n");
                print_token(tokens);
                tokencp = tokens; // je reavance le curseur de ma copie
            }
        }
        is_redirec = 1;
        // apres avoir etabli la branche de gauche je malloc la branche de droite
        // je me replace a l'adresse de la branche de droite dans mon nodes
        if(tokencp != NULL)
        {
            nodescp->right = init_nodes();
            nodescp = nodescp->right;
            nodes = nodescp;
        }
    }
    return((void) 0);
}

int main()
{
    t_token *tokens;
    t_node *nodes;

    tokens = (t_token *)malloc(sizeof(t_token));
    t_token *tokenscp = tokens;
    tokens = ft_token(tokens);
    while(tokens != NULL)
    {
        if(tokens->value)
            printf("value %s\n", tokens->value[0]);
        tokens = tokens->next;
    }
    create_node(tokenscp, &nodes);
    printf("\n\n\nJe print tous les nodes\n\n");
    print_tree(nodes);
    printf("\n\n");
    return (0);
}
