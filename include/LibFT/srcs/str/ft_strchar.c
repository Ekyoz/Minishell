/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:42:46 by atresall          #+#    #+#             */
/*   Updated: 2024/04/29 15:42:46 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchar(const char *string, char c)
{
	int	i;

	i = -1;
	while (string[++i])
	{
		if (string[i] == c)
			return (i);
	}
	return (-1);
}
