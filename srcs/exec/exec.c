/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:02:43 by bpoyet            #+#    #+#             */
/*   Updated: 2024/03/29 15:17:39 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

void exec(void)
{
    // je check ce que c'est
    // je renvois vers la fonction associe
    // entre chaque variable je check si j'ai un pipe ou chevron ou double chevron
    // implementation de l'arbre ast me permettant de regrouper les commandes par deux 
    // soit commande - pipe - commande soit commande - chevron - commande 

    //dup2 pour rediriger > et <
    //open en append pour >> et <<

    char *args[] = {"cat", "-e","exec.c", NULL};

    if(execve("/usr/bin/cat", args, NULL) == -1)
        perror("pas bon");
        
}

void create_node(t_token *tokens)
{
    t_node *nodes;
    t_token *tokencp;

    nodes = (t_node*)malloc(sizeof(t_node));
    if(!nodes)
        perror("Malloc Error");
    if(tokens->next == NULL)
    {
        // j'appelle une fonction qui execute seulement une commande
    }
    while(tokencp->next != NULL)
    {
        // je stocke dans ma liste les pipe en premier
        while(tokencp->next != NULL)
        {
            if(tokencp->type = TOKEN_PIPE)
            {
                nodes->right->type = TOKEN_PIPE;
                
            }
            tokencp = tokencp->next;
        }
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

