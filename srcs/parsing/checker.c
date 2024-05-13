/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:17:19 by atresall          #+#    #+#             */
/*   Updated: 2024/05/03 17:49:22 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool checker_word(t_token **head, char *command);
bool checker_pipe(t_token **head, char *command);
bool checker_redire_out(t_token **head, char *command);
bool checker_redire_in(t_token **head, char *command);
bool checker_redire_append(t_token **head, char *command);
bool checker_redire_heredoc(t_token **head, char *command);
bool checker_env_var(t_token **head, char *command);
bool checker_or(t_token **head, char *command);
bool checker_and(t_token **head, char *command);


bool checker(t_token **head, char *command)
{
	if (!checker_word(head, command))
		return false;
	else if (!checker_redire_in(head, command))
		return false;
	else if (!checker_redire_out(head, command))
		return false;
	else if (!checker_redire_append(head, command))
		return false;
	else if (!checker_redire_heredoc(head, command))
		return false;
//	else if (!checker_pipe(head, command))
//		return false;
//	else if (!checker_env_var(head, command))
//		return false;
//	else if (!checker_or(head, command))
//		return false;
//	else if (!checker_and(head, command))
//		return false;
	return true;
}

bool checker_pipe(t_token **head, char * command)
{
	size_t i = -1;
	char *input;
	int count_redir_out = 0;
	while (command[++i])
	{
		if (command[i] == '|')
		{
			if (command[i+1] == '|')
				count_redir_out++;
			if (i == 0)
			{
				clear_list(head);
				return false;
			}
			else if (i == ft_strlen(command)-1 && command[i-1] != '|')
			{
				input = readline("> ");
				delete_token(head,get_last_token(*head));
				parsing(head, input);
			}
		}
		else if (command[i+1] != '|')
		{
			if (count_redir_out < 2)
				count_redir_out = 0;
		}
	}
	if (count_redir_out >= 2)
	{
		clear_list(head);
		return false;
	}
	return (true);
}

bool checker_redire_out(t_token **head, char *command)
{
	size_t i = -1;
	int count_redir_out = 0;
	while (command[++i])
	{
		if (command[i] == '>')
		{
			if (command[i+1] == '>')
				count_redir_out++;
			else if (i == ft_strlen(command)-1)
			{
				clear_list(head);
				return false;
			}
			else if (i == 0)
				delete_token(head, *head);
		}
		else if (command[i+1] != '>')
		{
			if (count_redir_out < 2)
				count_redir_out = 0;
		}
	}
	if (count_redir_out >= 2)
	{
		clear_list(head);
		return false;
	}
	return (true);
}

bool checker_redire_in(t_token **head, char *command)
{
	size_t i = -1;
	int count_redir_in = 0;
	while (command[++i])
	{
		if (command[i] == '<')
		{
			if (command[i+1] == '<')
				count_redir_in++;
			else if (i == ft_strlen(command)-1)
			{
				clear_list(head);
				return false;
			}
			else if (i == 0)
				delete_token(head, *head);
		}
		else if (command[i+1] != '<')
		{
			if (count_redir_in < 2)
				count_redir_in = 0;
		}
	}
	if (count_redir_in >= 2)
	{
		clear_list(head);
		return false;
	}
	return (true);
}

bool checker_redire_append(t_token **head, char *command)
{
	size_t i = -1;
	int count_redir_in = 0;
	while (command[++i])
	{
		if (command[i] == '>' && command[i+1] == '>')
		{
			if (command[i+1] == '>')
				count_redir_in++;
			if (i == ft_strlen(command))
			{
				clear_list(head);
				return false;
			}
			if (i == 0)
				delete_token(head, *head);
		}
		else if (command[i+1] != '>' )
		{
			if (count_redir_in < 2)
				count_redir_in = 0;
		}
	}
	if (count_redir_in >= 2)
	{
		clear_list(head);
		return false;
	}
	return (true);
}

bool checker_redire_heredoc(t_token **head, char *command)
{
	size_t i = -1;
	int count_redir_in = 0;
	while (command[++i])
	{
		if (command[i] == '<' && command[i+1] == '<')
		{
			if (command[i+1] == '<')
				count_redir_in++;
			if (i == ft_strlen(command))
			{
				clear_list(head);
				return false;
			}
			if (i == 0)
				delete_token(head, *head);
		}
		else if (command[i+1] != '<' )
		{
			if (count_redir_in < 2)
				count_redir_in = 0;
		}
	}
	if (count_redir_in >= 2)
	{
		clear_list(head);
		return false;
	}
	return (true);
}

bool checker_word(t_token **head, char *command)
{
	(void) head;
	(void) command;
	return true;
}