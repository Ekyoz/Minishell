/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:11:57 by alexandre         #+#    #+#             */
/*   Updated: 2023/11/27 17:13:07 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_fd(unsigned int num, const char *base, int fd)
{
	unsigned int	base_len;
	int				count;

	count = 0;
	base_len = ft_strlen(base);
	if (num < base_len)
	{
		count += ft_putchar_fd(base[num], fd);
		return (count);
	}
	else
	{
		count += ft_puthex_fd(num / base_len, base, fd);
		count += ft_puthex_fd(num % base_len, base, fd);
	}
	return (count);
}
