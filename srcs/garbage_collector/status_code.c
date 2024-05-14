/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:41 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/14 11:25:55 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void read_status(t_tree *tree)
{
    printf("%d\n", tree->statuscode);
    // je sais pas quoi exit apres avoir fait cette commande 
}