/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:07 by atresall          #+#    #+#             */
/*   Updated: 2024/06/19 15:33:18 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_list(char **list, char *element);

char	**miss_elements(char **l_base, char **l_to_miss)
{
	int		base_length;
	char	**result;
	int		result_index;

	base_length = ft_arrlen(l_base);
	result = (char **)malloc((base_length + 1) * sizeof(char *));
	if (!result)
		return ((char **) NULL);
	result_index = 0;
	while (*l_base)
	{
		if (!is_in_list(l_to_miss, *l_base))
			result[result_index++] = ft_strdup(*l_base);
		l_base++;
	}
	result[result_index] = NULL;
	if (result_index == 0)
		return (free_array(&result), NULL);
	return (result);
}

static int	is_in_list(char **list, char *element)
{
	while (*list)
	{
		if (strcmp(*list, element) == 0)
		{
			return (1);
		}
		list++;
	}
	return (0);
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
