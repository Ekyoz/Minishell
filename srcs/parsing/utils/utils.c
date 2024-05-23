/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:55:21 by atresall          #+#    #+#             */
/*   Updated: 2024/05/22 15:13:25 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_array(char **array)
{
	if (array == NULL)
		return;
	int i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

char **ft_arraydup(char **array)
{
	int i = -1;
	char **dup = (char **) malloc(sizeof (char *) * (ft_strlen_array(array) +1));

	while (array[++i])
		dup[i] = ft_strdup(array[i]);
	dup[i] = NULL;
	return dup;
}

char *join_array(char **cmd)
{
	int len = (int)ft_strlen_array(cmd);
	// Calcul de la taille totale nécessaire pour la chaîne résultante
	int total_length = 0;
	for (int i = 0; i < len; i++) {
		total_length += (int)ft_strlen(cmd[i]) + 1; // +1 pour l'espace entre chaque mot
	}

	// Allocation de mémoire pour la chaîne résultante
	char *result = (char *)malloc(total_length + 1); // +1 pour le caractère nul de fin de chaîne
	if (result == NULL) {
		printf("Erreur lors de l'allocation de mémoire.\n");
		exit(1);
	}

	// Copie des chaînes avec des espaces entre elles dans la chaîne résultante
	int index = 0;
	for (int i = 0; i <(int) len; i++) {
		ft_strcpy(&result[index], cmd[i]);
		index += (int)ft_strlen(cmd[i]);
		if (i < len - 1) {
			result[index] = ' '; // Ajout d'un espace entre chaque mot
			index++;
		}
	}
	result[index] = '\0'; // Ajout du caractère nul de fin de chaîne

	return result;
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
	else if (type == TOKEN_WORD)
		printf("\033[0;94m\033[1mTOKEN\033[0m: WORD\n");
	else if (type == TOKEN_OR)
		printf("\033[0;94m\033[1mTOKEN\033[0m: OR\n");
	else if (type == TOKEN_AND)
		printf("\033[0;94m\033[1mTOKEN\033[0m: AND\n");
}

void printList(t_token * node) {
	int i = 0;
	printf("\n");
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
	printf("Nombre total de tokens: \033[0;31m\033[1m%d\033[0m\n\n", i);
}