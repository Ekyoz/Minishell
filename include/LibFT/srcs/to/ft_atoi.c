/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:13:24 by atresall          #+#    #+#             */
/*   Updated: 2023/11/24 11:19:42 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	verif_input(unsigned long long n)
{
	if (n > ULLONG_MAX)
		return (-1);
	if (n < ULLONG_MAX)
		return (0);
	return (n);
}

int	ft_atoi(const char *str)
{
	unsigned long long	nb;
	size_t				i;
	int					sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	nb = sign * nb;
	return (verif_input(nb));
}
