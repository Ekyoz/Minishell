/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/14 00:50:21 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

int get_pipe(t_token *token, t_node *nodes)
{
    t_token *tokencp;

    tokencp = token;
    while(token->type != TOKEN_PIPE)
    {
        token = token->next;
    }
    if(token->type == TOKEN_PIPE)
    {
        nodes->type = TOKEN_PIPE; // 
        token->type = PIPEUSED; // je mets le type a NULL une fois que je lai stocke
        token = tokencp;
        return (1); // je retourne 1 dans le cas ou je trouve un pipe
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de pipe
}
int get_redirection_left(t_token *token, t_node *nodes)
{
    t_token *tokencp;

    tokencp = token;
    while(token->type != TOKEN_REDIR_IN || token->type != TOKEN_REDIR_OUT || 
        token->type != TOKEN_REDIR_APPEND || token->type != TOKEN_REDIR_HEREDOC || 
        token->type != PIPEUSED)
    {
        token = token->next;
    }
    if(token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || 
        token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC)
    {
        nodes->left = init_nodes(nodes);
        if(token->type == TOKEN_REDIR_IN)
            nodes->left->type = TOKEN_REDIR_IN;
        else if(token->type == TOKEN_REDIR_OUT)
            nodes->left->type = TOKEN_REDIR_OUT;        
        else if(token->type == TOKEN_REDIR_OUT)
            nodes->left->type = TOKEN_REDIR_OUT;        
        else
            nodes->left->type = TOKEN_REDIR_OUT;        
        token->type = REDIRUSED; // je mets le type a NULL une fois que je lai stocke
        token = tokencp;
        nodes = nodes->left; // j'avance dans mon arbre si il y a une redirection
        return (1); // je retourne 1 dans le cas ou je trouve une redirection
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de redirection    
}

int get_redirection_right(t_token *token, t_node *nodes)
{
    t_token *tokencp;

    tokencp = token;
    while(token->type != TOKEN_REDIR_IN || token->type != TOKEN_REDIR_OUT || 
        token->type != TOKEN_REDIR_APPEND || token->type != TOKEN_REDIR_HEREDOC || 
        token->type != PIPEUSED)
    {
        token = token->next;
    }
    if(token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || 
        token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC)
    {
        nodes->right = init_nodes(nodes);
        if(token->type == TOKEN_REDIR_IN)
            nodes->right->type = TOKEN_REDIR_IN;
        else if(token->type == TOKEN_REDIR_OUT)
            nodes->right->type = TOKEN_REDIR_OUT;        
        else if(token->type == TOKEN_REDIR_OUT)
            nodes->right->type = TOKEN_REDIR_OUT;        
        else
            nodes->right->type = TOKEN_REDIR_OUT;        
        token->type = REDIRUSED; // je mets le type a NULL une fois que je lai stocke
        token = tokencp;
        nodes = nodes->right; // j'avance dans mon arbre si il y a une redirection
        return (1); // je retourne 1 dans le cas ou je trouve une redirection
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de redirection    
}

void create_node(t_token *tokens)
{
    t_node *nodes;
    t_node *nodescp; // copie de node qui va contenir l'addresse de la branche right du potentiel prochain pipe
    t_token *tokencp;

    tokencp = tokens;
    nodes = init_nodes(nodes);
    if(!nodes)
        return(NULL);
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
            nodes->is_pipe = 1; // je mets la variable a 1 pour dire que jai bien trouve un pipe
            // il faut aussi que je stocke l'adresse du right
            printf("j'ai bien un pipe\n"); 
        }
        // Ensuite je stocke les redirections
        if(nodes->is_pipe == 1)
        {
            // ma premiere redirection passe a gauche
            if(get_redirection_left(tokencp, nodes)) 
            {
                // mes autres redirections a droite si j'ai d'autres redirections
            }
            else
            {
                // jeffectue une commande
            }
        }
        else
        {
            // si j'ai pas de pipe je crois que ca revient au meme quand meme
        }

        nodes->is_pipe = 0; // je la remets a 0
        tokencp = tokencp->next;
    }
}

int main(int argc, char *argv[], char *envp[])
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
    
    return 0;
}

    // dans exec
    // je check ce que c'est
    // je renvois vers la fonction associe
    // entre chaque variable je check si j'ai un pipe ou chevron ou double chevron
    // implementation de l'arbre ast me permettant de regrouper les commandes par deux 
    // soit commande - pipe - commande soit commande - chevron - commande 

    //dup2 pour rediriger > et <
    //open en append pour >> et <<