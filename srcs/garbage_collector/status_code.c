/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:41 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/16 22:57:19 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void read_status(t_tree *tree)
{
    (void)tree;
    printf("%d\n", signal_status);
    // je sais pas quoi exit apres avoir fait cette commande 
}