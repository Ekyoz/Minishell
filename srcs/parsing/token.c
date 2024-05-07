/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:09:50 by atresall          #+#    #+#             */
/*   Updated: 2024/05/03 17:49:26 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token(t_token_type type, char **value)
{
	t_token *token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return NULL;
	token->type = type;
	token->value = value;
	token->next = NULL;
	return token;
}

void append_token(t_token **head, t_token_type type, char **value)
{
	t_token *next_token = create_token(type, value);
	if (next_token == NULL)
		return;
	t_token *last_token = *head;
	if (*head == NULL)
	{
		*head = next_token;
		return ;
	}
	while (last_token->next != NULL)
		last_token = last_token->next;
	last_token->next = next_token;
}

void delete_token(t_token **head, t_token *node_to_delete)
{
	t_token *prev;
	t_token *temp;
	if (*head == NULL || node_to_delete == NULL)
		return;

	if (*head == node_to_delete)
		*head = node_to_delete->next;

	prev = NULL;
	temp = *head;

	while (temp != NULL && temp != node_to_delete)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL)
		return;

	prev->next = temp->next;

	free(temp);
}

t_token *get_last_token(t_token *head)
{
	t_token *last_token = head;
	while (last_token->next != NULL)
		last_token = last_token->next;
	return last_token;
}

void clear_list(t_token **head)
{
    t_token *current = *head;
    t_token *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}