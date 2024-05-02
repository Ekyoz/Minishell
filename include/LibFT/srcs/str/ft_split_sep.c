/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:49:24 by atresall          #+#    #+#             */
/*   Updated: 2024/04/30 14:49:24 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int count_separators(const char* string, char separator) {
	int count = 0;
	int length = ft_strlen(string);
	int i = 0;
	while (i < length) {
		if (string[i] == separator) {
			count++;
		}
		i++;
	}
	return count;
}

char** allocate_memory(int count) {
	return (char**)malloc((count * 2 + 1) * sizeof(char*));
}

void split_string(char** result, char* string, char separator) {
	int length = ft_strlen(string);
	int index = 0;
	int start = 0;
	int i = 0;

	// Vérifie si le premier caractère est un séparateur
	if (string[0] == separator) {
		start = 1;
	}

	while (i <= length) {
		if (string[i] == separator || string[i] == '\0') {
			int substring_length = i - start;
			// Vérifie si la sous-chaîne n'est pas vide
			if (substring_length > 0) {
				result[index] = (char*)malloc((substring_length + 1) * sizeof(char));
				ft_strlcpy(result[index], string + start, substring_length + 1);
				index++;
			}
			if (string[i] == separator) {
				result[index] = (char*)malloc(2 * sizeof(char));
				result[index][0] = separator;
				result[index][1] = '\0';
				index++;
			}
			start = i + 1;
		}
		i++;
	}

	// Vérifie si le dernier caractère est un séparateur
	if (string[length - 1] == separator) {
		result[index] = (char*)malloc(2 * sizeof(char));
		result[index][0] = separator;
		result[index][1] = '\0';
		index++;
	}
}

char** ft_split_sep(char* string, char separator) {
	int separator_count = count_separators(string, separator);
	char** result = allocate_memory(separator_count);
	split_string(result, string, separator);
	return result;
}
