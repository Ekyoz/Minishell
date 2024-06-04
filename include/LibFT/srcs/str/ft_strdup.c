/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:58:54 by atresall          #+#    #+#             */
/*   Updated: 2024/06/04 17:08:18 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	size_t	i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * (ft_strlen(source) + 1));
	if (dst == NULL || source == NULL)
		return (NULL);
	while (source[i])
	{
		dst[i] = source[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
