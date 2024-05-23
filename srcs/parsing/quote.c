/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:28:56 by atresall          #+#    #+#             */
/*   Updated: 2024/05/22 16:00:51 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_text(char **cmd);
static char **del_array(char **array, int index);

char **quote(char **cmd)
{
	if (!quoted(cmd))
		return cmd;

	int first_quote[2];
	int last_quote[2];
	char c_quote;
	get_first_quote(cmd, first_quote, &c_quote);
	get_last_quote(cmd, last_quote, &c_quote);

	for (int i = 0; cmd[i]; i++)
	{
		printf("cmd[%d]: %s\n", i, cmd[i]);
	}


	printf("first quote: [%d][%d] = %c\n", first_quote[0], first_quote[1], c_quote);
	printf("last quote: [%d][%d] = %c\n", last_quote[0], last_quote[1], c_quote);

	return cmd;
}

// char **quote(char **cmd)
// {
// 	int diff;
// 	char *text;
// 	char first_quote;
// 	char **temp;
// 	int i_temp = 0;
//
// 	while (is_open(cmd) != 0)
// 		cmd = add_text(cmd);
//
// 	first_quote = get_first_quote_char(cmd, NULL);
//
// 	temp = ft_arraydup(cmd);
//
// 	while ((quote_len(temp, '\'') > 0 || quote_len(temp, '"') > 0))
// 	{
// 		diff = get_last_quote(temp, first_quote) - get_first_quote(temp, first_quote);
// 		text = get_text(temp);
// 		printf("text: %s\n", text);
// 		if (diff > 0)
// 		{
// 			while (diff > 0)
// 			{
// 				temp = del_array(temp,get_last_quote(temp, first_quote)-diff+1);
// 				diff--;
// 			}
// 		}
// 		temp[get_first_quote(temp,first_quote)] = ft_strdup(text);
// 		free(text);
// 		cmd = temp;
// 		temp = ft_arraydup(&cmd[get_last_quote(temp, first_quote)+1]);
// 		printf("test\n");
// 	}
//
// 	return cmd;
// }

// static char *get_text(char **cmd)
// {
// 	int i_cmd = -1;
// 	int i_final = 0;
// 	int j_cmd;
// 	int l_final = 0;
// 	char first_quote = get_first_quote_char(cmd, &l_final);
// 	char *c_final;
// 	char *before;
// 	char *after;
//
// 	if (first_quote == 0)
// 		return NULL;
//
// 	j_cmd = ft_strchar(cmd[get_first_quote(cmd, first_quote)], first_quote)+1; // position[2] de la premiere quote
//
// 	cmd = &cmd[get_first_quote(cmd, first_quote)];
//
// 	c_final = (char *)malloc(sizeof(char) * (l_final+1));
//
// 	while (i_cmd < get_last_quote(cmd, first_quote) && cmd[++i_cmd])
// 	{
// 		while (cmd[i_cmd][j_cmd] && cmd[i_cmd][j_cmd] != first_quote)
// 		{
// 			c_final[i_final++] = cmd[i_cmd][j_cmd];
// 			j_cmd++;
// 		}
// 		j_cmd = 0;
// 	}
//
// 	c_final[i_final] = '\0';
//
// 	before = ft_substr(cmd[get_first_quote(cmd, first_quote)], 0,ft_strchar(cmd[get_first_quote(cmd, first_quote)], first_quote));
// 	if (get_last_quote(cmd, first_quote) == get_first_quote(cmd, first_quote))
// 		after = ft_substr(cmd[get_last_quote(cmd, first_quote)], ft_strlen(before) + ft_strlen(c_final)+2, ft_strlen(cmd[get_first_quote(cmd, first_quote)]));
// 	else
// 	{
// 		after = ft_substr(cmd[get_last_quote(cmd, first_quote)],ft_strchar(cmd[get_last_quote(cmd, first_quote)], first_quote)+1,
// 						  ft_strlen(cmd[get_last_quote(cmd, first_quote)]) + ft_strchar(cmd[get_last_quote(cmd, first_quote)], first_quote));
// 	}
// 	c_final = ft_strcat(before, c_final);
//  	c_final = ft_strcat(c_final, after);
//
// 	return c_final;
// }


static char **del_array(char **array, int index) {
	int size = (int)ft_strlen_array(array);

	if (index < 0 || index >= size) {
		printf("Index hors limites.\n");
		return array;
	}

	// Sauvegarde de la chaîne à l'index spécifié
	char *removed_string = array[index];

	// Libération de la mémoire occupée par la chaîne supprimée
	free(removed_string);

	// Déplacement des éléments suivants vers la gauche pour remplir le vide
	for (int i = index; i < (size) - 1; i++) {
		array[i] = array[i + 1];
	}

	// Réduction de la taille du tableau
	(size)--;

	// Réallocation de la mémoire pour réduire la taille du tableau
	char **temp = (char **)realloc(array, sizeof(char *) * (size));
	if (temp == NULL) {
		printf("Erreur lors de la réallocation de mémoire.\n");
		exit(1);
	}

	temp[size] = NULL;


	return temp;
}