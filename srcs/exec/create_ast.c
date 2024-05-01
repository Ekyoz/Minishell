/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/01 12:18:44 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_print_branch(t_node *node)
{
    printf("Actuelle gauche %d\n", node->type);
    if(node->args)
        printf("l'args vaut %s\n", node->args[0]);
    if(node->left)
    {
        printf("left %d\n", node->left->type);
        if(node->right)
        {
            printf("right %d\n", node->right->type);
            // printf("right %d %s\n", node->right->type, node->right->args[0]);
            get_print_branch(node->right);
        }
    }
}

void print_tree(t_node *node)
{
    while(node != NULL)
    {
        printf("premier ou droite %d\n", node->type);
        if(node->args)
            printf("l'args vaut %s\n", node->args[0]);
        if(node->left)
            get_print_branch(node->left);
        node = node->right;
    }
    printf("\n\n");
}

static void check_left_redirec(t_node **nodes, t_token **token, bool *is_redirec)
{
    *nodes = (*nodes)->left;// je suis sur la redirection
    while(*is_redirec == 1)
    { 
        add_node_left(*nodes, token);
        if(get_redirection_right(*token, *nodes)) // je regarde a droite si j'ai une redirection
            *nodes = (*nodes)->right; // decalle branche de droite    
        else // pas d'autres redirections donc c'est une commande, il faut que j'arrive a recuperer la bonne commande
            add_node_right(*nodes, token, is_redirec);
    }
}

void create_node(t_token *tokens, t_tree **tree)
{
    t_node *nodes;
    t_node *nodescp; // copie de node qui va contenir l'addresse de la branche right du potentiel prochain pipe
	bool is_redirec; // boolean a 1 si une redirec est sur ma branche

    is_redirec = 1;
    nodes = init_nodes();
    if(!nodes)
        return((void) 1);
    nodescp = nodes; // une recopie pour stocker le premier node
    (*tree)->nodes = nodescp;
    if(tokens->next == NULL)
    {
        add_node(nodes, &tokens);
        return((void) 1);
    }
    while(tokens != NULL)
    {
        if(get_pipe(tokens, nodes))// Je stocke dans ma liste les pipe en premier
        {
            if(get_redirection_left(tokens, nodes)) // tant que j'ai des redirections sur la branche de gauche ma premiere redirection passe a gauche
                check_left_redirec(&nodes, &tokens, &is_redirec);
            else // je fais une commande a gauche
                add_node_left(nodes, &tokens);
        }
        else
        {
            if(get_redirection_main(tokens, nodes)) // CONDITION pas de pipe je verifie si j'ai une redirection
                add_node_left(nodes, &tokens);
            else // si j'en ai pas j'effectue une commande
                add_node(nodes, &tokens);
        }
        add_branches(tokens, &nodes, &nodescp, &is_redirec);
    }
    printf("\n\n");
    return((void) 0);
}

int main(int argc, char *argv[], char *envp[])
{
    (void)argc;
    (void)argv;
    char *input;
    t_token *tokens;
    t_tree *tree;

    tree = init_tree(envp);
    if(!tree)
        return (1);
    while (true)
    {
        input = readline("Minishell :");
        add_history(input);
		tokens = parsing(input);
        create_node(tokens, &tree);
        printf("\n");
        print_tree(tree->nodes);
        ast_exec(tree);
        if(!ft_strncmp(input, "exit", 5))
            break;
    }
    return 0;
}
