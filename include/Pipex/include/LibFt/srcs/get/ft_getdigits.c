/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdigits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:55:39 by atresall          #+#    #+#             */
/*   Updated: 2023/11/27 12:53:08 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getdigits(long long num)
{
	size_t		count;
	long long	nbr;

	count = 0;
	if (num < 0)
	{
		count++;
		nbr = num * -1;
	}
	else
	{
		nbr = num;
	}
	while (nbr > 0)
	{
		count++;
		nbr = nbr / 10;
	}
	return (count);
}
