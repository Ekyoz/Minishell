/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:14:41 by atresall          #+#    #+#             */
/*   Updated: 2023/11/17 15:15:53 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*element_new;

	if (!elementCount || !elementSize)
		return (malloc(0));
	if (elementCount > (size_t)(-1) / elementSize)
		return (NULL);
	element_new = (void *)malloc(elementSize * elementCount);
	if (!element_new)
		return (NULL);
	ft_bzero(element_new, elementCount * elementSize);
	return (element_new);
}
