/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:07 by atresall          #+#    #+#             */
/*   Updated: 2024/06/11 14:17:33 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_in_list(char **list, char *element);

char	**miss_elements(char **l_base, char **l_to_miss) {
	int	base_length	= ft_arrlen(l_base);
	char	**result = (char **)malloc((base_length + 1) * sizeof(char *));

	if (!result) {
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	int result_index = 0;
	while (*l_base) {
		if (!is_in_list(l_to_miss, *l_base)) {
			result[result_index++] = ft_strdup(*l_base);
		}
		l_base++;
	}

	result[result_index] = NULL;

	return result;
}

static int is_in_list(char **list, char *element) {
	while (*list) {
		if (strcmp(*list, element) == 0) {
			return 1; // Trouvé
		}
		list++;
	}
	return 0; // Pas trouvé
}

char	**string_to_array(char *string)
{
	char	**array;

	array = (char **)malloc(2 * sizeof(char *));
	if (!array)
		return (NULL);
	array[0] = ft_strdup(string);
	array[1] = NULL;
	return (array);
}

char	**clean_space(char **cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (ft_arrlen(cmd) == 1)
		while (cmd[0][++i])
			if (ft_isspace(cmd[0][i]))
				return (cmd);
	i = -1;
	while (cmd[++i])
	{
		if (ft_strcmp(cmd[i], " ") != 0)
			cmd[j++] = cmd[i];
		else
			free(cmd[i]);
	}
	cmd[j] = NULL;
	return (cmd);
}
