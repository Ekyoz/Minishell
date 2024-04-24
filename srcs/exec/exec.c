/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:48 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/24 16:01:45 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *execute_command(t_tree *tree, t_node *nodes)
{
    pid_t pid;
    
    pid = fork();
    if(pid == -1 )
        return((void *)1);
    if(pid == 0)
    {
        printf("child process\n");
        tree->path = check_access1(tree, nodes);
        if(execve(tree->path, nodes->args, NULL) == -1)
        {
            printf("error execve\n");
            return((void*)1);
        }
    }
    waitpid(pid, NULL, 0);
    return((void*)0);
}

void redirec_out(t_tree *tree, t_node *nodes)
{
    int fd;

    // javance tant que j'ai des redirections out
    while(nodes->right->type == TOKEN_REDIR_OUT)
    {
        nodes = nodes->right;
    }
    fd = open(nodes->args[0], O_TRUNC | O_CREAT | O_WRONLY, 0644);
    if(fd < 0)
    {
        printf("pas bien de pas ouvrir les fichiers\n");
    }
}

void redirection(t_tree *tree, t_node *nodes)
{
    if(nodes->type == TOKEN_REDIR_OUT)
    {

    }
}

void ast_exec(t_tree *tree)
{
    t_node *nodes;

    nodes = tree->nodes;
    while(nodes != NULL)
    {
        if(nodes->type == TOKEN_PIPE)
        {
            printf("dans un pipe\n");
        }
        else if(nodes->type == TOKEN_REDIR_IN || nodes->type == TOKEN_REDIR_OUT || 
        nodes->type == TOKEN_REDIR_APPEND || nodes->type == TOKEN_REDIR_HEREDOC)
        {
            printf("dans une redirection tabernak\n");
        }
        else if(nodes->type == TOKEN_WORD)
        {
            printf("dans une commande\n");
            execute_command(tree, nodes);
        }
        else
        {
            printf("dans aucun\n");
        }
        nodes = nodes->right;
    }
}