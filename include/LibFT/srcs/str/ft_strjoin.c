/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:02:58 by atresall          #+#    #+#             */
/*   Updated: 2023/11/17 19:14:52 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	o;
	size_t	size;
	char	*out;

	i = -1;
	o = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!s1 || !s2)
		return (NULL);
	out = (char *)malloc(sizeof(char) * size);
	if (!out)
		return (NULL);
	while (s1[++i])
		out[o++] = s1[i];
	i = -1;
	while (s2[++i])
		out[o++] = s2[i];
	out[o] = '\0';
	return (out);
}
