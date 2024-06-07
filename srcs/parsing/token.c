/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:09:50 by atresall          #+#    #+#             */
/*   Updated: 2024/06/07 12:47:11 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *create_token(t_token_type type, char **value);

static void free_array1(char **ptr)
{
    int i;
    
    i = 0;
	if (ptr)
	{
		while(ptr[i])
		{
			// printf("freeing %p et %s\n", ptr[i], ptr[i]);
			free(ptr[i]);
			i++;
		}
		// printf("freeing %p\n", ptr);
		free(ptr);
		ptr = NULL;
	}
}

void append_token(t_token **head, t_token_type type, char **value)
{
	t_token *last_token = *head;
	if (*head == NULL)
	{
		*head = create_token(type, ft_arrdup(value));
		return ;
	}
	while (last_token->next != NULL)
		last_token = last_token->next;
	last_token->next = create_token(type, ft_arrdup(value));
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

static t_token *create_token(t_token_type type, char **value)
{
	t_token *token = (t_token *) malloc(sizeof(t_token)*1);
	if (!token)
		return NULL;
	token->type = type;
    token->value = NULL;
	if (value != NULL && (type == TOKEN_WORD || type == TOKEN_REDIR_HEREDOC))
	{
		token->value = clean_space(value);
		printf("clean space  %p %s type %d\n", token->value[0], token->value[0], token->type);
	}
	else
	{
		printf("dans le free array\n");
		free_array1(value);
	}
	// if(token->value)
	// 	printf("value = %p %s\n", token->value[0], token->value[0]);
	token->next = NULL;
	return token;
}

void clear_token(t_token **head)
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