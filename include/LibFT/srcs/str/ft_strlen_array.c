/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:19:39 by atresall          #+#    #+#             */
/*   Updated: 2024/05/07 14:23:18 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_array(char **array)
{
	size_t size = 0;
	// Parcourt le tableau jusqu'à trouver un pointeur NULL
	while (array[size] != NULL) {
		size++;
	}
	return size;
}