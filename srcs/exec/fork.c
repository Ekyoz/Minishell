/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:17:34 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/21 16:25:57 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t do_fork(t_tree *tree, pid_t pid)
{
    (void)tree;
    pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        exit(1);
    }
    return (pid);
}