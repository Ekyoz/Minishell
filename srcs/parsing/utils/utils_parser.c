/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:07 by atresall          #+#    #+#             */
/*   Updated: 2024/05/03 17:49:20 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **extract_flags(char **command) {
	char **c_flag;
	char *first_flag = command[0];
	int i_count = -1;
	int i_flags = 1;
	int i_command = 0;
	int count = 0;

	while (command[++i_count])
		if (command[i_count][0] == '-')
			count++;

	c_flag = (char **)malloc((count + 2) * sizeof(char *));
	c_flag[0] = (char *)malloc((ft_strlen(first_flag) + 1) * sizeof(char));

	ft_strcpy(c_flag[0], first_flag);

	while (command[++i_command])
	{
		if (command[i_command][0] == '-')
		{
			c_flag[i_flags] = (char *)malloc((ft_strlen(command[i_command]) + 1) * sizeof(char));
			ft_strcpy(c_flag[i_flags], command[i_command]);
			i_flags++;
		}
		else if (command[i_command][0] != '-')
			break;
	}

	c_flag[i_flags] = NULL;

	return c_flag;
}

char **miss_elements(char **l_base, char **l_miss) {
	int s_base = 0;
	int i_missing = 0;
	int i_base = -1;
	int i_miss = 0;
	char **missing;
	bool find = false;

	while (l_base[s_base])
		s_base++;

	missing = (char**)malloc((s_base + 1) * sizeof(char*));

	while (l_base[++i_base])
	{
		i_miss = -1;
		find = false;
		while (l_miss[++i_miss])
		{
			if (ft_strcmp(l_base[i_base], l_miss[i_miss]) == 0)
			{
				find = true;
				break;
			}
		}
		if (!find)
			missing[i_missing++] = ft_strdup(l_base[i_base]);
	}

	return missing;
}

char **string_to_array(char *string)
{
	char **array;
	array = (char **)malloc(2 * sizeof(char *));
	array[0] = ft_strdup(string);
	array[1] = NULL;
	return array;
}

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
			for (int j = 1; node->value[j]; j++)
				printf("\033[0;33m\033[1mARGS[%d]\033[0m: %s\n",j , node->value[j]);
		}
		printf("===============================\n");
		printf("\n");
		node = node->next;
	}
	printf("Nombre total de tokens: \033[0;31m\033[1m%d\033[0m\n", i);
}