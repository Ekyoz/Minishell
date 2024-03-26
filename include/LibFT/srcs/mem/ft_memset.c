/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:16:30 by atresall          #+#    #+#             */
/*   Updated: 2023/11/17 15:01:20 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t size)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = pointer;
	while (i < size)
	{
		tmp[i] = value;
		i++;
	}
	return (pointer);
}
