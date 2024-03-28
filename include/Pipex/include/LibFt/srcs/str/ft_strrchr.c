/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:55 by atresall          #+#    #+#             */
/*   Updated: 2023/11/16 17:29:13 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*s;

	s = (char *)str;
	while (*s != '\0')
		s++;
	while (*s != (char)ch && str != s)
		s--;
	if (*s == (char)ch)
		return (s);
	else
		return (0);
}
