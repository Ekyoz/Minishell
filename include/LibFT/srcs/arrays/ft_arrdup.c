/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:40:08 by atresall          #+#    #+#             */
/*   Updated: 2024/06/07 12:39:50 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_arrdup(char **array)
{
	int		i;
	char	**dup;

	i = -1;
	if (array == NULL)
		return (NULL);
	printf("size du malloc %lu -%s- \n", sizeof(char*) *(ft_arrlen(array) + 1), array[0]);
	dup = (char **)malloc(sizeof(char *) * (ft_arrlen(array) + 1));
	if (dup == NULL)
		return (NULL);
	while (array[++i])
	{
		dup[i] = ft_strdup(array[i]);
		printf("dup %p %s %d\n", dup[i], dup[i], i);
	}
	dup[i] = NULL;
	return (dup);
}
