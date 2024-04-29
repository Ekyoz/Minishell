/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:48 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/29 16:17:38 by bpoyet           ###   ########.fr       */
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

void *exec_pipe(t_tree *tree, t_node *nodes)
{
    char *buffer;

    buffer = (char *)malloc(sizeof(char) * BUFFER);
    pid_t pid[3];
    int i;
    int j;
    int k;

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
            // fprintf(stderr, "j vaut %d\n", j);
            if(j == 0) // premier pipe
            {
                dup2(tree->fdpipe[j][1], STDOUT_FILENO);
                k = 0;
                while(k < i)
                {
                    close(tree->fdpipe[k][0]);
                    close(tree->fdpipe[k][1]);
                    k++;
                }
                // close(tree->fdpipe[j][1]);
                // close(tree->fdpipe[j][0]);
            }
            else if(j == i) // dernier pipe
            {
                dup2(tree->fdpipe[j - 1][0], STDOUT_FILENO);
                k = j - 1;
                while(k < i)
                {
                    close(tree->fdpipe[k][0]);
                    close(tree->fdpipe[k][1]);
                    k++;
                }
                // close(tree->fdpipe[j - 1][0]);
                // close(tree->fdpipe[j - 1][1]);
            }
            else // pipe(s) du milieu 
            {
                dup2(tree->fdpipe[j - 1][0], STDIN_FILENO); // je lis mon pipe actuelle
                dup2(tree->fdpipe[j][1], STDOUT_FILENO);
                k = j - 1;
                while(k < i)
                {
                    close(tree->fdpipe[k][0]);
                    close(tree->fdpipe[k][1]);
                    k++;
                }
                // close(tree->fdpipe[j - 1][0]);
                // close(tree->fdpipe[j][1]);
                // close(tree->fdpipe[j][0]);
                // close(tree->fdpipe[j - 1][1]);
            }
            if(nodes->left)
                tree->path = check_access1(tree, nodes->left);
            else
                tree->path = check_access1(tree, nodes);
            fprintf(stderr, "le path %s\n", tree->path);
            if(execve(tree->path, nodes->args, NULL) == -1)
            {
                fprintf(stderr, "error execve\n");
                return((void*)1);
            }
        }
        else
        {
            // if(j > 0)
            //     close(tree->fdpipe[j - 1][0]);
            // if(j < i)
            //     close(tree->fdpipe[j][1]);
            k = 0;
            while(k < i)
            {
                close(tree->fdpipe[k][0]);
                close(tree->fdpipe[k][1]);
                k++;
            }
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
            fprintf(stderr, "j vaut %d\n", j);
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

void *exec_cmd_out(t_tree *tree, t_node *nodes, int fd)
{
    pid_t pid;

    pid = fork();
    if(pid == -1)
        return ((void*)1);
    if(pid == 0)
    {
        printf("child process\n");
        dup2(fd, STDOUT_FILENO);
        close(fd);
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

void *redirec_out(t_tree *tree, t_node *nodes)
{
    int i;
    int fd;
    t_node *nodecp; // je garde ma commande dans un nodecp

    i = 0;
    // printf("ma commande left %d\n", nodes->left->type);
    if(nodes->left->type == TOKEN_WORD)
    {
        printf("je stocke ma commande dans une copie\n");
        nodecp = nodes->left;
    }
    else
    {
        printf("error token inexistant %d\n", nodes->left->type);
        return ((void*) 1);
    }
    // javance tant que j'ai des redirections out et j'ouvre les fichiers
    while(nodes->type == TOKEN_REDIR_OUT)
    {
            if(nodes->left->args)
            {
                fd = open(nodes->left->args[0], O_TRUNC | O_CREAT | O_WRONLY, 0644);
                if(fd < 0)
                    return (void*)0;
            }
            if(nodes->right->args)
            {
                fd = open(nodes->right->args[0], O_TRUNC | O_CREAT | O_WRONLY, 0644);
                if(fd < 0)
                    return (void*)0;
            }
        nodes = nodes->right;
    }
    //j'appelle une fonction qui effectue une commande et qui redirige
    exec_cmd_out(tree, nodecp, fd);
    return ((void*) 0);
}

void redirection(t_tree *tree, t_node *nodes, int *out)
{
    if(nodes->type == TOKEN_REDIR_OUT)
    {
        redirec_out(tree, nodes);
    }
    *out = 0;
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
            // J'execute la branche de gauche que je redirige a l'entree de mon pipe
            
        }
        else if(nodes->type == TOKEN_REDIR_IN || nodes->type == TOKEN_REDIR_OUT || 
        nodes->type == TOKEN_REDIR_APPEND || nodes->type == TOKEN_REDIR_HEREDOC)
        {
            redirection(tree, nodes, &out);
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