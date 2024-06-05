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

bool check_input(char *input)
{
    int i;
    int space;

    space = 0;
    i = 0;
    while (input[++i])
    {
        if (ft_isprint(input[i]) == 0)
            exit(128);
        if (ft_isspace(input[i]))
            space++;
    }
    if (space == (int)ft_strlen(input)-1)
        return false;
    return true;
}