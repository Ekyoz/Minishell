/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:09:50 by atresall          #+#    #+#             */
/*   Updated: 2024/06/20 16:28:59 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_token(t_token_type type, char **value);

void	append_token(t_token **head, t_token_type type, char **value)
{
	t_token	*last_token;

	last_token = *head;
	if (!value && type == TOKEN_WORD)
		return ;
	if (*head == NULL)
	{
		*head = create_token(type, ft_arrdup(value));
		return ;
	}
	while (last_token->next != NULL)
		last_token = last_token->next;
	last_token->next = create_token(type, ft_arrdup(value));
}

void	delete_token(t_token **head, t_token *node_to_delete)
{
	t_token	*prev;
	t_token	*temp;

	if (*head == NULL || node_to_delete == NULL)
		return ;
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
	{
		return ;
	}
	prev->next = temp->next;
	free_array(&node_to_delete->value);
	free(temp);
}

static t_token	*create_token(t_token_type type, char **value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (!token)
		return (NULL);
	token->type = type;
	token->value = NULL;
	if (value != NULL && (type == TOKEN_WORD || type == TOKEN_REDIR_HEREDOC))
		token->value = clean_space(value);
	else
		free_array(&value);
	token->next = NULL;
	return (token);
}

void	clear_token(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

