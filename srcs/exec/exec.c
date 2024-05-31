/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:48 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/31 16:49:25 by bastpoy          ###   ########.fr       */
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
        signal_status = WEXITSTATUS(status);
    }

}

void *ft_execve(t_tree *tree, t_node *nodes)
{
    fprintf(stderr, "je suis dans lexec\n");
    tree->path = check_access1(tree, nodes);
    if(execve(tree->path, nodes->args, env_to_string(tree, tree->env)) == -1)
    {
        perror("");
        return((void*)1);
    }
    return((void*)0);
}

int exec_cmd(t_tree *tree, t_node *nodes)
{
    pid_t pid;
    int status;

    status = 0;
    if(choose_builtin(tree, nodes))
        return(0);
    pid = fork();
    set_signal_cmd();
    if(pid == -1 )
        err_free_all(tree);
    if(pid == 0)
    {
        if(!check_cmd1(tree, nodes))
            print_error(2, tree, nodes);
        tree->path = check_access1(tree, nodes);
        if(execve(tree->path, nodes->args, env_to_string(tree, tree->env)) == -1)
            err_free_all(tree);
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
        do_unset(nodes->left, tree->env);
    pid = do_fork(tree, pid);
    if(pid == 0)
    {
        hdoc_or_cmd(nodes);
        heredoc(tree, nodes);
        check_redir_out(tree, nodes);
        check_redir_in(tree, nodes);
        if(choose_builtin(tree, nodes->left))
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
}
