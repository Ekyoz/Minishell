/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:30:06 by atresall          #+#    #+#             */
/*   Updated: 2024/05/13 15:30:06 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char* ft_strcat(char* destination, const char* source) {
	char* ptr = destination;

	// Finding the end of the destination string
	while (*ptr != '\0') {
		ptr++;
	}

	// Appending the source string to the destination string
	while (*source != '\0') {
		*ptr = *source;
		ptr++;
		source++;
	}

	// Adding the null terminator to the concatenated string
	*ptr = '\0';

	return destination;
}