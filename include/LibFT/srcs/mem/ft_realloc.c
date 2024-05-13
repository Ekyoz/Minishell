/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:22 by atresall          #+#    #+#             */
/*   Updated: 2024/02/13 15:03:25 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr = malloc(new_size);
	if (new_ptr == NULL) {
		return NULL; // Échec de l'allocation
	}

	// Copie des données de l'ancien bloc vers le nouveau
	ft_memcpy(new_ptr, ptr, old_size);

	// Libération de l'ancien bloc
	free(ptr);

	return new_ptr;
}


