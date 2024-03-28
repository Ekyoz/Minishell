/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:37:04 by alexandre         #+#    #+#             */
/*   Updated: 2023/11/27 17:13:47 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(uintptr_t num, const char *base, int fd)
{
	uintptr_t	base_len;
	int			count;

	count = 0;
	base_len = (uintptr_t)ft_strlen(base);
	if (num < base_len)
		return (ft_putchar_fd(base[num], fd));
	else
	{
		count += ft_putptr_fd(num / base_len, base, fd);
		count += ft_putptr_fd(num % base_len, base, fd);
	}
	return (count);
}
