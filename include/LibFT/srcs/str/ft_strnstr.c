/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:58:13 by atresall          #+#    #+#             */
/*   Updated: 2023/11/17 15:33:33 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *source, const char *search, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!*search)
		return ((char *)source);
	while (source[i])
	{
		j = 0;
		while (source[i] == search[j] && source[i] && i < size)
		{
			i++;
			j++;
		}
		if (!search[j])
			return ((char *)&source[i - j]);
		i = (i - j) + 1;
	}
	return (NULL);
}
