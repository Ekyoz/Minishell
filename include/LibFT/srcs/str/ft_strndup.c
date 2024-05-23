/*                                                                            */
/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:45:10 by atresall          #+#    #+#             */
/*   Updated: 2024/05/16 14:45:10 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(char *str, size_t n) {
	char *new_str = (char *)malloc((n + 1) * sizeof(char));
	if (new_str == NULL)
		return NULL;

	ft_strlcpy(new_str, str, n);

	new_str[n] = '\0';

	return new_str;
}