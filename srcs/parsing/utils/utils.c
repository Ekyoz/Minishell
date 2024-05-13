/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:55:21 by atresall          #+#    #+#             */
/*   Updated: 2024/05/07 14:23:55 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *next_word(char *cmd, int pos)
{
	char **l_words;

	if (pos > (int)ft_strlen(cmd)-1)
		return NULL;

	l_words = splitter(cmd);
	return l_words[pos+1];
}

void add_element_n(char ***list_ptr, int pos, char *value)
{
	char** list = *list_ptr;
	int listSize = ft_strlen_array(*list_ptr);
	printf("listSize: %d\n", listSize);

	// Augmente la taille de la liste
	list = realloc(list, (listSize + 1) * sizeof(char*));

	// Décale les chaînes vers la droite pour faire de la place pour la nouvelle chaîne
	for (int i = listSize; i > pos; i--) {
		list[i] = list[i - 1];
	}

	// Alloue de la mémoire pour la nouvelle chaîne et copie la valeur
	list[pos] = malloc((strlen(value) + 1) * sizeof(char));
	strcpy(list[pos], value);

	// Met à jour la liste et sa taille via les pointeurs
	*list_ptr = list;
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