/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/03/29 12:25:46 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exec(t_token *token)
{
    // je check ce que c'est
    // je renvois vers la fonction associe
    // entre chaque variable je check si j'ai un pipe ou chevron ou double chevron
    // implementation de l'arbre ast me permettant de regrouper les commandes par deux 
    // soit commande - pipe - commande soit commande - chevron - commande 
}

void create_node(t_token *token)
{
    while(token->next == NULL)
    {
        
    }
}
