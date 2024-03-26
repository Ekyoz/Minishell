/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:20 by atresall          #+#    #+#             */
/*   Updated: 2023/11/14 11:12:18 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t		i;
	char		*tmp_dest;
	const char	*tmp_source;

	i = 0;
	tmp_dest = destination;
	tmp_source = source;
	if (!destination && !source)
		return (NULL);
	while (i < size)
	{
		tmp_dest[i] = tmp_source[i];
		i++;
	}
	return (destination);
}
