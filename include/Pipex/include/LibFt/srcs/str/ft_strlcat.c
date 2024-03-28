/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:54:39 by atresall          #+#    #+#             */
/*   Updated: 2023/11/10 12:11:31 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *destination, const char *source, size_t size)
{
	size_t	c;
	size_t	d;

	if (size <= ft_strlen(destination))
		return (size + ft_strlen(source));
	c = ft_strlen(destination);
	d = 0;
	while (source[d] != '\0' && c + 1 < size)
	{
		destination[c] = source[d];
		c++;
		d++;
	}
	destination[c] = '\0';
	return (ft_strlen(destination) + ft_strlen(&source[d]));
}
