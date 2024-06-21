/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:19:39 by atresall          #+#    #+#             */
/*   Updated: 2024/05/07 14:23:18 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrlen(char **array)
{
	size_t	size;

	size = 0;
	if (!array)
		return (0);
	while (array[size])
	{
		size++;
	}
	return (size);
}
