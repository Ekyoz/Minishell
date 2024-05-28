/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_twodim_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:40:03 by bastpoy           #+#    #+#             */
/*   Updated: 2024/05/27 16:46:45 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_array(void **ptr)
{
    int i;
    
    i = 0;
    while(ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    if(ptr)
        free(ptr);
    ptr = NULL;
}