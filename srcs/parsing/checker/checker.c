/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:17:19 by atresall          #+#    #+#             */
/*   Updated: 2024/05/17 13:23:37 by atresall         ###   ########.fr       */
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
