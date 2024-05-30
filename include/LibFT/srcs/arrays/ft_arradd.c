/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:35:13 by atresall          #+#    #+#             */
/*   Updated: 2024/05/24 11:35:13 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arradd(char **array, char *line)
{
	int		i;
	int		length;
	char	**new_array;

	i = -1;
	length = ft_arrlen(array);
	new_array = (char **)malloc((length + 2) * sizeof(char *));
	if (new_array == NULL)
		return (NULL);
	while (++i < length)
		new_array[i] = array[i];
	new_array[length] = line;
	new_array[length + 1] = NULL;
	free(array);
	return (new_array);
}
