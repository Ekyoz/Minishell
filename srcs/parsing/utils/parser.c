/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:07 by atresall          #+#    #+#             */
/*   Updated: 2024/05/15 13:03:46 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_missing(char *element, char **l_miss);

char	**miss_elements(char **l_base, char **l_miss)
{
	int		i_base;
	int		i_missing;
	char	**missing;

	i_base = 0;
	i_missing = 0;
	missing = (char **)malloc((ft_arrlen(l_base) + 1) * sizeof(char *));
	if (!missing)
		return (NULL);
	while (l_base[i_base])
	{
		if (is_missing(l_base[i_base], l_miss))
			missing[i_missing++] = ft_strdup(l_base[i_base]);
		i_base++;
	}
	missing[i_missing] = NULL;
	return (missing);
}

char	**string_to_array(char *string)
{
	char	**array;

	array = (char **)malloc(2 * sizeof(char *));
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

static bool	is_missing(char *element, char **l_miss)
{
	int	i;

	i = 0;
	while (l_miss[i])
	{
		if (ft_strcmp(element, l_miss[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}
