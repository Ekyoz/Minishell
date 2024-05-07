/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:48 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/07 17:36:43 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void *ft_execve(t_tree *tree, t_node *nodes)
{
    tree->path = check_access1(tree, nodes);
    if(execve(tree->path, nodes->args, NULL) == -1)
    {
        fprintf(stderr, "error execve\n");
        perror("error");
        return((void*)1);
    }
    return((void*)0);
}

void *exec_cmd(t_tree *tree, t_node *nodes)
{
    pid_t pid;
    
    pid = fork();
    if(pid == -1 )
        return((void *)1);
    if(pid == 0)
    {
        if(!check_cmd1(tree, nodes))
            print_error(1, nodes, tree);
        tree->path = check_access1(tree, nodes);
        if(execve(tree->path, nodes->args, NULL) == -1)
        {
            perror("error");
            return((void*)1);
        }
    }
    waitpid(pid, NULL, 0);
    return((void*)0);
}

void *exec_cmd_out(t_tree *tree, t_node *nodes)
{
    pid_t pid;

    pid = fork();
    if(pid == -1)
        return ((void*)1);
    if(pid == 0)
    {
        if(!check_cmd1(tree, nodes))
            exit(2);
        heredoc(tree, nodes);
        check_redir_out(tree, nodes);
        check_redir_in(tree, nodes);
        ft_execve(tree, nodes->left);
    }
    else
    {
        waitpid(pid, NULL, 0);
        if(access(".here_doc", F_OK) != -1)
            unlink(".here_doc");
    }
    return((void*)0);
}

void ast_exec(t_tree *tree)
{
    t_node *nodes;
    int out;
    errno = 0;

    out = 1;
    nodes = tree->nodes;
    while(out == 1)
    {
        if(nodes->type == TOKEN_PIPE)
        {
            printf("dans un pipe\n");
            exec_pipe(tree, nodes);
            out = 0;            
        }
        else if(nodes->type == TOKEN_REDIR_IN || nodes->type == TOKEN_REDIR_OUT || 
        nodes->type == TOKEN_REDIR_APPEND || nodes->type == TOKEN_REDIR_HEREDOC)
        {
            printf("dans redir\n");
            exec_cmd_out(tree, nodes);
            out = 0;
        }
        else if(nodes->type == TOKEN_WORD)
        {
            exec_cmd(tree, nodes);
            out = 0;
        }
        else
        {
            printf("dans aucun\n");
        }
        nodes = nodes->right;
    }
}
