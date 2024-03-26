/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:09:07 by atresall          #+#    #+#             */
/*   Updated: 2023/11/16 17:53:21 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	size_t	i;

	if (destination == NULL && source == NULL)
		return (NULL);
	if (source <= destination)
	{
		while (n--)
		{
			((unsigned char *)destination)[n] = ((unsigned char *)source)[n];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
			i++;
		}
	}
	return (destination);
}
