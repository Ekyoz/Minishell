/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:29:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/16 15:28:00 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        nodes->type = TOKEN_PIPE; //je met mon type a used
        token->type = PIPEUSED; // je mets le type a USED une fois que je lai stocke
        token = tokencp; // je reviens en arriere dans ma liste chainee apres avoir trouve le token
        return (1); // je retourne 1 dans le cas ou je trouve un pipe
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de pipe
}

int get_redirection_left(t_token *token, t_node *nodes)
{
    t_token *tokencp;

    tokencp = token;
    while(token->type != TOKEN_REDIR_IN && token->type != TOKEN_REDIR_OUT && 
        token->type != TOKEN_REDIR_APPEND && token->type != TOKEN_REDIR_HEREDOC && 
        token->type != PIPEUSED)
    {
        token = token->next;
    }
    if(token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || 
        token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC)
    {
        nodes->left = init_nodes();
        if(token->type == TOKEN_REDIR_IN)
            nodes->left->type = TOKEN_REDIR_IN;
        else if(token->type == TOKEN_REDIR_OUT)
            nodes->left->type = TOKEN_REDIR_OUT;        
        else if(token->type == TOKEN_REDIR_OUT)
            nodes->left->type = TOKEN_REDIR_OUT;        
        else
            nodes->left->type = TOKEN_REDIR_OUT;        
        token->type = REDIRUSED; // je mets le type a NULL une fois que je lai stocke
        token = tokencp; // je reviens en arriere dans ma liste chainee apres avoir trouve le token
        // nodes = nodes->left; // j'avance dans mon arbre si il y a une redirection
        return (1); // je retourne 1 dans le cas ou je trouve une redirection
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de redirection    
}

int get_redirection_right(t_token *token, t_node *nodes)
{
    t_token *tokencp;

    tokencp = token;
    while(token->type != TOKEN_REDIR_IN && token->type != TOKEN_REDIR_OUT && 
        token->type != TOKEN_REDIR_APPEND && token->type != TOKEN_REDIR_HEREDOC && 
        token->type != PIPEUSED)
    {
        token = token->next;
    }
    if(token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || 
        token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC)
    {
        nodes->right = init_nodes();
        if(token->type == TOKEN_REDIR_IN)
            nodes->right->type = TOKEN_REDIR_IN;
        else if(token->type == TOKEN_REDIR_OUT)
            nodes->right->type = TOKEN_REDIR_OUT;        
        else if(token->type == TOKEN_REDIR_OUT)
            nodes->right->type = TOKEN_REDIR_OUT;        
        else
            nodes->right->type = TOKEN_REDIR_OUT;        
        token->type = REDIRUSED; // je mets le type a NULL une fois que je lai stocke
        token = tokencp; // je reviens en arriere dans ma liste chainee apres avoir trouve le tokenp;
        nodes = nodes->right; // j'avance dans mon arbre si il y a une redirection
        return (1); // je retourne 1 dans le cas ou je trouve une redirection
    }
    else
        return(0); //je retourne 0 dans le cas ou j'ai pas de redirection    
}
