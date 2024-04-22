/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/22 17:55:39 by bpoyet           ###   ########.fr       */
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
        printf("token %d -", tokens->type);
        tokens = tokens->next;
    }
    printf("\n");
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
        printf("Actuelle gauche %d\n", node->type);
        printf("left %d\n", node->left->type);
        if(node->right)
        {
            printf("right %d\n", node->right->type);
            get_print_branch(node->right);
        }
    }
}

void print_tree(t_node *node)
{
    while(node != NULL)
    {
        printf("premier ou droite %d\n", node->type);
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
            printf("pipe\n");
            // tant que j'ai des redirections sur la branche de gauche
            // ma premiere redirection passe a gauche
            if(get_redirection_left(tokencp, nodes)) 
            {
                nodes = nodes->left;// je suis sur la redirection
                while(is_redirec == 1)
                { 
                    add_node_left(nodes, tokens);
                    tokens = tokens->next; // je saute la redirection donc deux next
                    if(tokens != NULL && (tokens->type == PIPEUSED || tokens->type == REDIRUSED))
                        tokens = tokens->next; // Je passe au prochain token
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
                        tokens = tokens->next; // je saute la redirection donc deux next
                        if(tokens != NULL && (tokens->type == PIPEUSED || tokens->type == REDIRUSED))
                            tokens = tokens->next; // Je passe au prochain token
                        tokencp = tokens; // je reavance le curseur de ma copie
                        is_redirec = 0;
                    }
                }
            } 
            else // je fais une commande a gauche
            {
                add_node_left(nodes, tokens);
                printf("jajoute a gauche\n");
                tokens = tokens->next; // Je passe au prochain token
                if(tokens != NULL && (tokens->type == PIPEUSED || tokens->type == REDIRUSED))
                    tokens = tokens->next; // Je passe au prochain token
                printf("le token a gauche %d\n", tokens->type);
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
                printf("dans la redirection main\n");
                add_node_left(nodes, tokens);
                printf("le node left %d\n", nodes->left->type);
                print_token(tokens);
                tokens = tokens->next;
                if(tokens != NULL && (tokens->type == PIPEUSED || tokens->type == REDIRUSED))
                    tokens = tokens->next; // Je passe au prochain token
                tokencp = tokens; // je reavance le curseur de ma copie
            }
            // si j'en ai pas j'effectue une commande
            else
            {
                add_node(nodes, tokens);
                printf("le node %d\n", nodes->type);
                print_token(tokens);
                tokens = tokens->next;
                if(tokens != NULL && (tokens->type == PIPEUSED || tokens->type == REDIRUSED))
                    tokens = tokens->next; // Je passe au prochain token
                printf("Pas de redirection a droite\n");
                // print_token(tokens);
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
    char *input;
    t_token *tokens;
    t_node *nodes;

    while (true)
    {
        input = readline("Minishell :");
		printf("Line: %d\n", input[0]);
        add_history(input);
		tokens = parsing(input);
        create_node(tokens, &nodes);
        printf("\n");
        print_tree(nodes);
        if(!ft_strncmp(input, "exit", 5))
            break;
    }
    return 0;
}
