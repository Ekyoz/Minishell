/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:01:14 by atresall          #+#    #+#             */
/*   Updated: 2024/05/27 10:01:14 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdel(char **array, int del)
{
	int		count;
	int		i;
	char	**new_array;

	count = 0;
	if (array == NULL || del < 0)
		return (array);
	count = ft_arrlen(array);
	if (del >= count)
		return (array);
	free(array[del]);
	i = del - 1;
	while (++i < count - 1)
		array[i] = array[i + 1];
	array[count - 1] = NULL;
	new_array = ft_realloc(array, (count) * sizeof(char *), (count + 1)
			* sizeof(char *));
	if (new_array == NULL && count > 1)
		return (array);
	return (new_array);
}
