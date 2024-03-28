/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:59:14 by atresall          #+#    #+#             */
/*   Updated: 2023/11/16 11:04:12 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int searchChar)
{
	while (*str)
	{
		if (*str == (char)searchChar)
			return ((char *)str);
		str++;
	}
	if (*str == (char)searchChar)
		return ((char *)str);
	else
		return (NULL);
}
