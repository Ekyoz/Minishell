/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:17:19 by atresall          #+#    #+#             */
/*   Updated: 2024/04/19 14:17:29 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void checker_word(t_token *head, char *command);
void checker_pipe(t_token *head, char *command);
bool checker_redire_out(t_token *head, char *command);
void checker_redire_in(t_token *head, char *command);
void checker_redire_append(t_token *head, char *command);
void checker_redire_heredoc(t_token *head, char *command);
void checker_env_var(t_token *head, char *command);
void checker_or(t_token *head, char *command);
void checker_and(t_token *head, char *command);


bool checker(t_token *head, char *command)
{
	bool err;
	err = checker_redire_out(head, command);
	return err;
}

bool checker_redire_out(t_token *head, char *command)
{
	int i = -1;
	t_token *current = head;

	while (current != NULL)
	{
		if (current->type == TOKEN_REDIR_OUT)
		{
			while (command[++i] != '>');
			if (check_char_before(command, '>', i, 2))
				return (false);
			if (check_char_after(command, '>', i, 2))
				return (false);
		}
		current = current->next;
	}
	return (true);
}

