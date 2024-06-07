/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:17:19 by atresall          #+#    #+#             */
/*   Updated: 2024/06/07 10:40:51 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void checker(t_token **head)
{
    t_token *token = *head;
    t_token *next_token;

    while (token)
    {
        next_token = token->next;
        if (token->type == TOKEN_WORD && token->value[0] == NULL)
            delete_token(head, token);
        token = next_token;
    }
}
