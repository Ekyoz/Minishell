/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:29:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/20 20:02:07 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_pipe(t_token *token, t_node *nodes)
{
    // t_token *tokencp;

    // tokencp = token;
    while(token != NULL && token->type != TOKEN_PIPE)
    {
        token = token->next;
    }
    if(token != NULL && token->type == TOKEN_PIPE)
    {
        nodes->type = TOKEN_PIPE; //je met mon type a used
        token->type = PIPEUSED; // je mets le type a USED une fois que je lai stocke
        nodes->args = token->value;        
        return (1); // je retourne 1 dans le cas ou je trouve un pipe
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de pipe
}

int get_redirection_left(t_token *token, t_node *nodes)
{
    // t_token *tokencp;

    // tokencp = token;
    while(token != NULL && token->type != TOKEN_REDIR_IN && token->type != TOKEN_REDIR_OUT && 
        token->type != TOKEN_REDIR_APPEND && token->type != TOKEN_REDIR_HEREDOC && 
        token->type != PIPEUSED)
    {
        token = token->next;
    }
    if(token != NULL && (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || 
        token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC))
    {
        nodes->left = init_nodes();
        nodes->left->type = token->type;
        nodes->left->args = token->value;
        token->type = REDIRUSED; // je mets le type a NULL une fois que je lai stocke
        printf("le type a left %d\n", nodes->left->type);
        // token = tokencp; // je reviens en arriere dans ma liste chainee apres avoir trouve le token
        return (1); // je retourne 1 dans le cas ou je trouve une redirection
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de redirection    
}

int get_redirection_right(t_token *token, t_node *nodes)
{
    t_token *tokencp;

    tokencp = token;
    while(token != NULL && token->type != TOKEN_REDIR_IN && token->type != TOKEN_REDIR_OUT && 
        token->type != TOKEN_REDIR_APPEND && token->type != TOKEN_REDIR_HEREDOC && 
        token->type != PIPEUSED)
    {
        token = token->next;
    }
    if(token != NULL && (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || 
        token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC))
    {
        nodes->right = init_nodes();
        nodes->right->type = token->type;
        nodes->right->args = token->value;;        
        token->type = REDIRUSED; // je mets le type a NULL une fois que je lai stocke
        token = tokencp; // je reviens en arriere dans ma liste chainee apres avoir trouve le tokenp;
        // nodes = nodes->right; // j'avance dans mon arbre si il y a une redirection
        return (1); // je retourne 1 dans le cas ou je trouve une redirection
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de redirection    
}

int get_redirection_main(t_token *token, t_node *nodes)
{
    while(token != NULL && token->type != TOKEN_REDIR_IN && token->type != TOKEN_REDIR_OUT && 
        token->type != TOKEN_REDIR_APPEND && token->type != TOKEN_REDIR_HEREDOC && 
        token->type != PIPEUSED)
    {
        token = token->next;
    }
    if(token != NULL && (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || 
        token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC))
    {
        if(!nodes)
            nodes = init_nodes();
        nodes->type = token->type;
        nodes->args = token->value;      
        token->type = REDIRUSED; // je mets le type a NULL une fois que je lai stocke
        return (1); // je retourne 1 dans le cas ou je trouve une redirection
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de redirection    
}