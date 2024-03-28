/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:08:24 by alexandre         #+#    #+#             */
/*   Updated: 2023/11/27 16:00:36 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoh(size_t num)
{
	char	*hex_string;
	int		i;
	int		remainder;

	hex_string = (char *)malloc(sizeof(char) * 17);
	i = 0;
	while (num != 0)
	{
		remainder = num % 16;
		if (remainder < 10)
		{
			hex_string[i++] = 48 + remainder;
		}
		else
		{
			hex_string[i++] = 87 + remainder;
		}
		num /= 16;
	}
	hex_string[i] = '\0';
	ft_strrev(hex_string);
	return (hex_string);
}
