/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:48 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/23 10:42:56 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parent_process(int status, pid_t pid)
{
    waitpid(pid, &status, 0);
    if(access(".here_doc", F_OK) != -1)
        unlink(".here_doc");
    if(WIFEXITED(status))
    {
        // fprintf(stderr, "le status vaut %d\n", status);
        signal_status = WEXITSTATUS(status);
    }

}

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
    pid = fork();
    set_signal_cmd();
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
    get_signal_cmd(status, pid);
    return(0);
}

void *exec_cmd_out(t_tree *tree, t_node *nodes)
{
    pid_t pid;
    int status;

    pid = 0;
    status = 0;
    if(nodes->left)
        unset_export(nodes->left, tree->env);
    hdoc_or_cmd(nodes);
    pid = do_fork(tree, pid);
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
    parent_process(status, pid);
    return((void*)0);
}

void ast_exec(t_tree *tree)
{
    t_node *nodes;
    
    nodes = tree->nodes;
    if(nodes->type == TOKEN_PIPE)
    {
        exec_pipe(tree, nodes);
    }
    else if(nodes->type == TOKEN_REDIR_IN || nodes->type == TOKEN_REDIR_OUT || 
    nodes->type == TOKEN_REDIR_APPEND || nodes->type == TOKEN_REDIR_HEREDOC)
    {
        exec_cmd_out(tree, nodes);
    }
    else if(nodes->type == TOKEN_WORD)
    {
        exec_cmd(tree, nodes);
    }
    else
        printf("dans aucun\n");
}
