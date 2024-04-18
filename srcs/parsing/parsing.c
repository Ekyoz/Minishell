/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:52:50 by atresall          #+#    #+#             */
/*   Updated: 2024/04/18 15:40:12 by atresall         ###   ########.fr       */
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
	return token;
}

void append_token(t_token **head, t_token_type type, char **value)
{
	t_token *next_token = create_token(type, value);
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

void print_token_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		printf("Token: PIPE\n");
	else if (type == TOKEN_REDIR_IN)
		printf("Token: REDIR_IN\n");
	else if (type == TOKEN_REDIR_OUT)
		printf("Token: REDIR_OUT\n");
	else if (type == TOKEN_REDIR_APPEND)
		printf("Token: REDIR_APPEND\n");
	else if (type == TOKEN_REDIR_HEREDOC)
		printf("Token: REDIR_HEREDOC\n");
	else if (type == TOKEN_ENV_VAR)
		printf("Token: ENV_VAR\n");
	else if (type == TOKEN_WORD)
		printf("Token: WORD\n");
}

void printList(t_token * node) {
	int i = 0;
	while(node != NULL) {
		printf("---------[ Token n %d ]---------\n", i);
		print_token_type(node->type);
		if (node->type == TOKEN_WORD)
		{
			printf("cmd[0]: %s\n", node->value[0]);
			printf("cmd[1]: %s\n", node->value[1]);
		} else
			printf("cmd: NULL\n");
		printf("------------------------------\n");
		printf("\n");
		node = node->next;
		i++;
	}
}


t_token *parsing(char *commands)
{
	int i = -1;
	int last_index = 0;
	t_token *head = NULL;
	while (commands[++i])
	{
		if(commands[i] == '|')
		{
			append_token(&head, TOKEN_WORD,
						 ft_split(ft_substr(commands, last_index, i - last_index), ' '));
			last_index = i+1;
			append_token(&head, TOKEN_PIPE, NULL);
//			break;
		}
		else if (commands[i] == '<')
		{
			append_token(&head, TOKEN_WORD,
						 ft_split(ft_substr(commands, last_index, i - last_index), ' '));
			last_index = i+1;
			append_token(&head, TOKEN_REDIR_IN, NULL);
//			break;
		}
		else if (commands[i] == '>')
		{
			append_token(&head, TOKEN_WORD,
						 ft_split(ft_substr(commands, last_index, i - last_index), ' '));
			last_index = i+1;
			append_token(&head, TOKEN_REDIR_OUT, NULL);
//			break;
		}
		else if (ft_strnstr(commands + i, ">>", 2)) {
			append_token(&head,TOKEN_WORD,ft_split(ft_substr(commands,last_index,i -last_index),' '));
			last_index =i + 1;
			append_token(&head,TOKEN_REDIR_APPEND,NULL);
		}
		else if (ft_strnstr(commands + i, "<<", 2)) {
			append_token(&head,TOKEN_WORD,ft_split(ft_substr(commands,last_index,i -last_index),' '));
			last_index =i + 1;
			append_token(&head,TOKEN_REDIR_HEREDOC,NULL);
		}
	}
	append_token(&head, TOKEN_WORD,
				 ft_split(ft_substr(commands, last_index, i - last_index), ' '));
	printList(head);
	return head;
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		parsing(av[1]);
	}
	return (0);
}