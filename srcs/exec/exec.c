/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:48 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/17 15:20:51 by bastpoy          ###   ########.fr       */
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

int exec_cmd(t_tree *tree, t_node *nodes)
{
    pid_t pid;
    int status;

    status = 0;
    if(choose_builtin(tree, nodes, tree->env) ||
        unset_export(nodes, tree->env))
        return(0);
    set_signal_cmd();
    pid = fork();
    if(pid == -1 )
        return(1);
    if(pid == 0)
    {
        if(!check_cmd1(tree, nodes))
            print_error(2, tree, nodes);
        tree->path = check_access1(tree, nodes);
        if(execve(tree->path, nodes->args, NULL) == -1)
        {
            perror("error");
            exit(EXIT_FAILURE);
        }
    }
    waitpid(pid, &status, 0);
    // if(WIFSIGNALED(status))
    // {
        // printf("dans le signal %d\n", signal_status);
        // signal_status = WTERMSIG(status);
        // printf("%d\n", signal_status);
    // }
    // if (signal_status != 0)
    //     return(1);
    if(WIFEXITED(status))
    {
        signal_status = WEXITSTATUS(status);
        fprintf(stderr, "le status vaut %d et %d\n", signal_status, status);
    }
    return(0);
}

void *exec_cmd_out(t_tree *tree, t_node *nodes)
{
    pid_t pid;
    int status;

    status = 0;
    if(nodes->left)
        unset_export(nodes->left, tree->env);
    if(is_heredoc(nodes))
        set_signal_heredoc();
    else
        set_signal_cmd();
    pid = fork();
    if(pid == -1)
        return ((void*)1);
    if(pid == 0)
    {
        heredoc(tree, nodes);
        check_redir_out(tree, nodes);
        check_redir_in(tree, nodes);
        if(choose_builtin(tree, nodes->left, tree->env))
            exit(0); 
        if(!check_cmd1(tree, nodes->left))
            print_error(2, tree, nodes->left);
        ft_execve(tree, nodes->left);
    }
    waitpid(pid, &status, 0);
    if(access(".here_doc", F_OK) != -1)
        unlink(".here_doc");
    if(WIFEXITED(status))
    {
        fprintf(stderr, "le status vaut %d\n", status);
        signal_status = WEXITSTATUS(status);
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
            exec_pipe(tree, nodes);
            out = 0;            
        }
        else if(nodes->type == TOKEN_REDIR_IN || nodes->type == TOKEN_REDIR_OUT || 
        nodes->type == TOKEN_REDIR_APPEND || nodes->type == TOKEN_REDIR_HEREDOC)
        {
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
