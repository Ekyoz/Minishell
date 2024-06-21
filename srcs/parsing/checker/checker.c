/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:17:19 by atresall          #+#    #+#             */
/*   Updated: 2024/06/19 15:32:14 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_token(t_token **head);

bool	checker(t_token **head)
{
	t_token	*token;
	t_token	*next_token;

	token = *head;
	while (token)
	{
		next_token = token->next;
		if (token->type == TOKEN_WORD && (token->value[0] == NULL
				|| ft_strcmp(token->value[0], " ") == 0))
			delete_token(head, token);
		token = next_token;
	}
	return (check_token(head));
}

bool	check_input(char *input)
{
	int	i;
	int	space;

	space = 0;
	i = -1;
	while (input[++i])
	{
		if (ft_isprint(input[i]) == 0 && ft_isspace(input[i] == 0))
			exit(128);
		if (ft_isspace(input[i]))
			space++;
	}
	if (space == (int)ft_strlen(input))
		return (false);
	return (true);
}

static bool	check_token(t_token **head)
{
	int		len;
	t_token	*token;

	len = 0;
	token = *head;
	while (token)
	{
		token = token->next;
		len++;
	}
	if (len == 1 && (*head)->type != TOKEN_WORD)
		return (false);
	return (true);
}
