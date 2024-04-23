/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:52:50 by atresall          #+#    #+#             */
/*   Updated: 2024/04/23 16:42:18 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		printf("\033[0;94m\033[1mTOKEN\033[0m: PIPE\n");
	else if (type == TOKEN_REDIR_IN)
		printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_IN\n");
	else if (type == TOKEN_REDIR_OUT)
		printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_OUT\n");
	else if (type == TOKEN_REDIR_APPEND)
		printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_APPEND\n");
	else if (type == TOKEN_REDIR_HEREDOC)
		printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_HEREDOC\n");
	else if (type == TOKEN_ENV_VAR)
		printf("\033[0;94m\033[1mTOKEN\033[0m: ENV_VAR\n");
	else if (type == TOKEN_WORD)
		printf("\033[0;94m\033[1mTOKEN\033[0m: WORD\n");
	else if (type == TOKEN_OR)
		printf("\033[0;94m\033[1mTOKEN\033[0m: OR\n");
	else if (type == TOKEN_AND)
		printf("\033[0;94m\033[1mTOKEN\033[0m: AND\n");
}

void printList(t_token * node) {
	int i = 0;
	while(node != NULL) {
		i++;
		printf("=========[ Token n %d ]=========\n", i);
		print_token_type(node->type);
		if (node->type == TOKEN_WORD)
		{
			printf("\033[0;31m\033[1mCOMMAND\033[0m: %s\n", node->value[0]);
//			for (int j = 1; node->value[j]; j++)
//				printf("\033[0;33m\033[1mARGS[%d]\033[0m: %s\n",j , node->value[j]);
		} else
			printf("\033[0;31m\033[1mCOMMAND\033[0m: NULL\n");
		printf("===============================\n");
		printf("\n");
		node = node->next;
	}
	printf("Nombre total de tokens: \033[0;31m\033[1m%d\033[0m\n", i);
}


bool parsing(t_token **head, char *commands)
{
	int i = -1;
	int last_index = 0;
	if (commands)
	{
		while (commands[++i])
		{
			if(commands[i] == '|' && commands[i + 1] != '|' && commands[i - 1] != '|')
			{
				append_token(head, TOKEN_WORD,ft_split(ft_substr(commands, last_index, i - last_index), ' '));
				append_token(head, TOKEN_PIPE, NULL);
				last_index = i+1;
			}
			else if (commands[i] == '$' && commands[i + 1] != ' ')
			{
				append_token(head, TOKEN_WORD,ft_split(ft_substr(commands, last_index, i - last_index), ' '));
				append_token(head, TOKEN_ENV_VAR, NULL);
				last_index = i+1;
			}
			else if(ft_strnstr(commands + i, "||", 2))
			{
				append_token(head, TOKEN_WORD,ft_split(ft_substr(commands, last_index, i - last_index), ' '));
				append_token(head, TOKEN_OR, NULL);
				last_index = i+2;
			}
			else if(ft_strnstr(commands + i, "&&", 2))
			{
				append_token(head, TOKEN_WORD,ft_split(ft_substr(commands, last_index, i - last_index), ' '));
				append_token(head, TOKEN_AND, NULL);
				last_index = i+2;
			}
			else if (commands[i] == '<' && commands[i + 1] != '<' && commands[i - 1] != '<')
			{
				append_token(head, TOKEN_WORD,ft_split(ft_substr(commands, last_index, i - last_index), ' '));
				append_token(head, TOKEN_REDIR_IN, NULL);
				last_index = i+1;
			}
			else if (commands[i] == '>' && commands[i + 1] != '>' && commands[i - 1] != '>')
			{
				append_token(head, TOKEN_WORD,ft_split(ft_substr(commands, last_index, i - last_index), ' '));
				append_token(head, TOKEN_REDIR_OUT, NULL);
				last_index = i+1;
			}
			else if (ft_strnstr(commands + i, ">>", 2) && commands[i+2] != '>' && commands[i-2] != '>') {
				append_token(head, TOKEN_WORD,ft_split(ft_substr(commands, last_index, i - last_index), ' '));
				append_token(head,TOKEN_REDIR_APPEND,NULL);
				last_index =i + 2;
			}
			else if (ft_strnstr(commands + i, "<<", 2) && commands[i+2] != '>' && commands[i-2] != '>') {
				append_token(head, TOKEN_WORD,ft_split(ft_substr(commands, last_index, i - last_index), ' '));
				append_token(head,TOKEN_REDIR_HEREDOC,NULL);
				last_index =i + 2;
			}
		}
		append_token(head, TOKEN_WORD,ft_split(ft_substr(commands, last_index, i - last_index), ' '));
	}
	if (!checker(head, commands))
		return false;
	return true;
}