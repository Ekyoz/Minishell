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

char	**miss_elements(char **l_base)
{
	int		i_base;
	int		i_missing;
	char	**missing;

	i_base = 0;
	i_missing = 0;
	missing = (char **)malloc((ft_arrlen(l_base) + 1) * sizeof(char *));
	if (!missing)
		return (NULL);
	while (l_base[i_base] && is_token(l_base[i_base], 0) == TOKEN_WORD)
	{
		missing[i_missing++] = ft_strdup(l_base[i_base]);
		i_base++;
	}
	if (i_missing == 0)
		return (free(missing), NULL);
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
