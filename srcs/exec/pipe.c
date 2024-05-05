/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:43:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/05 17:56:29 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int init_fdpipe(t_tree *tree,t_node *nodes)
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
    return (i);
}

static void dup_pipe(t_tree *tree, t_node *nodes, int j, int i)
{
    if(j == 0) // premier pipe
    {
        heredoc(tree, nodes->left);
        if(!check_redir_out(tree, nodes->left) || !check_redir_in(tree, nodes->left))
            dup2(tree->fdpipe[0][1], STDOUT_FILENO);
        check_redir_in(tree, nodes->left);
        close(tree->fdpipe[0][1]);
        close(tree->fdpipe[0][0]);
    }
    else if(j == i) // dernier pipe
    {
        heredoc(tree, nodes->left);
        check_redir_out(tree, nodes->left);
        dup2(tree->fdpipe[j - 1][0], STDIN_FILENO);
        close(tree->fdpipe[j - 1][0]);
        close(tree->fdpipe[j - 1][1]);
    }
    else // pipe(s) du milieu 
    {
        heredoc(tree, nodes->left);
        dup2(tree->fdpipe[j - 1][0], STDIN_FILENO); // je lis mon pipe actuelle
        // dup2(tree->fdpipe[j][1], STDOUT_FILENO); 
        if(!check_redir_out(tree, nodes->left))
            dup2(tree->fdpipe[j][1], STDOUT_FILENO);
        close(tree->fdpipe[j - 1][0]);
        close(tree->fdpipe[j - 1][1]);
        close(tree->fdpipe[j][0]);
        close(tree->fdpipe[j][1]);
    }
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
            dup_pipe(tree, nodes, j, i);
            if(check_redir_in(tree, nodes->left) || check_redir_out(tree, nodes->left)
                || find_heredoc(nodes->left))
                ft_execve(tree, nodes->left->left);
            else if(nodes->left)
            {
                fprintf(stderr,"type de cmd exec %d\n", nodes->left->type);
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
            waitpid(pid[j], NULL, 0);
            if(access(".here_doc", F_OK) != -1)
                unlink(".here_doc");
            j++;
            if(nodes->right)
                nodes = nodes->right;
        }
    }
        // j = 0;
        // while(j <= i)
        // {
        //     waitpid(pid[j], NULL, 0);
        //     j++;
        // }
    return ((void*)0);
}
