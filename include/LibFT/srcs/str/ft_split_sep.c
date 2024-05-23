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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	if (string[0] == separator) {
		start = 1;
	}

	while (i <= length) {
		if (string[i] == separator || string[i] == '\0') {
			int substring_length = i - start;
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

	if (string[length - 1] == separator) {
		result[index] = (char*)malloc(2 * sizeof(char));
		result[index][0] = separator;
		result[index][1] = '\0';
		index++;
	}
	result[index] = NULL;
}

char** ft_split_sep(char* str, char separator) {
	int len = ft_strlen(str);
	int capacity = 10;
	char **result = malloc(capacity * sizeof(char *));
	int count = 0;

	int start = 0;

	for (int i = 0; i <= len; i++) {
		if (str[i] == separator || str[i] == '\0') {
			if (start != i) {
				result[count] = strndup(str + start, i - start);
				count++;
				if (count >= capacity) {
					capacity *= 2;
					result = realloc(result, capacity * sizeof(char *));
				}
			}
			if (str[i] != '\0') {
				result[count] = strndup(str + i, 1);
				count++;
				if (count >= capacity) {
					capacity *= 2;
					result = realloc(result, capacity * sizeof(char *));
				}
			}
			start = i + 1;
		}
	}

	result[count] = NULL;
	return result;
}
