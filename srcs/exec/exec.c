/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:48 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/01 19:41:01 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_fdpipe(t_tree *tree,t_node *nodes)
{
    int j;
    int i;

    j = 0;
    i = 0;
    while(nodes->type == TOKEN_PIPE)
    {
        i++;
        nodes = nodes->right;
    }
    tree->fdpipe = (int **)malloc(sizeof(int*) * i); // je malloc le nombre de pipe
        // proteger les malloc
    while(j < i)
    {
        tree->fdpipe[j] = malloc(sizeof(int) * 2);
            // proteger les malloc
        if(pipe(tree->fdpipe[j]) == -1)
            perror("error creation pipe");
        j++;
    }
    printf("i vaut %d\n", i);
    return (i);
}

void *ft_execve(t_tree *tree, t_node *nodes)
{
    tree->path = check_access1(tree, nodes);
    if(execve(tree->path, nodes->args, NULL) == -1)
    {
        fprintf(stderr, "error execve\n");
        return((void*)1);
    }
    return((void*)0);
}

void *exec_pipe(t_tree *tree, t_node *nodes)
{
    pid_t pid[3];
    int i;
    int j;

    i = 0;
    j = 0;
    i = init_fdpipe(tree, nodes);
    while(j <= i)
    {
        pid[j] = fork();
        if(pid[j] < 0)
            perror("fork error");
        if(pid[j] == 0)
        {
            if(j == 0) // premier pipe
            {
                if(!check_redir_out(tree, nodes->left) || !check_redir_in(tree, nodes->left))
                    dup2(tree->fdpipe[0][1], STDOUT_FILENO);
                check_redir_in(tree, nodes->left);
                close(tree->fdpipe[0][1]);
                close(tree->fdpipe[0][0]);
            }
            else if(j == i) // dernier pipe
            {
                check_redir_out(tree, nodes->left);
                dup2(tree->fdpipe[j - 1][0], STDIN_FILENO);
                close(tree->fdpipe[j - 1][0]);
                close(tree->fdpipe[j - 1][1]);
            }
            else // pipe(s) du milieu 
            {
                dup2(tree->fdpipe[j - 1][0], STDIN_FILENO); // je lis mon pipe actuelle
                // dup2(tree->fdpipe[j][1], STDOUT_FILENO); 
                if(!check_redir_out(tree, nodes->left))
                    dup2(tree->fdpipe[j][1], STDOUT_FILENO);
                close(tree->fdpipe[j - 1][0]);
                close(tree->fdpipe[j - 1][1]);
                close(tree->fdpipe[j][0]);
                close(tree->fdpipe[j][1]);
            }
            if(check_redir_in(tree, nodes->left) || check_redir_out(tree, nodes->left))
                ft_execve(tree, nodes->left->left);
            else if(nodes->left)
            {
                ft_execve(tree, nodes->left);
            }
            else
                ft_execve(tree, nodes);
        }
        else
        {
            if(j > 0)
                close(tree->fdpipe[j - 1][0]);
            if(j < i)
                close(tree->fdpipe[j][1]);
            j++;
            if(nodes->right)
            {
                nodes = nodes->right;
            }
        }
    }
        j = 0;
        while(j <= i)
        {
            waitpid(pid[j], NULL, 0);
            j++;
        }
    return ((void*)0);
}

void *exec_cmd(t_tree *tree, t_node *nodes)
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

void *exec_cmd_out(t_tree *tree, t_node *nodes)
{
    pid_t pid;

    pid = fork();
    if(pid == -1)
        return ((void*)1);
    if(pid == 0)
    {
        check_redir_out(tree, nodes);
        check_redir_in(tree, nodes);
        ft_execve(tree, nodes->left);
    }
    waitpid(pid, NULL, 0);
    return((void*)0);
}

void ast_exec(t_tree *tree)
{
    t_node *nodes;
    int out;

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
