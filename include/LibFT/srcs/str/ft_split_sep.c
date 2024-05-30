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

static int	count_words(const char *str, char sep)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != sep && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == sep)
		{
			in_word = 0;
		}
		str++;
	}
	return (count);
}

static char	*word_dup(char *start, size_t len)
{
	char	*word;

	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static int	add_word(char **result, char *start, int len, int index)
{
	result[index] = word_dup(start, len);
	return (1);
}

static int	split_loop(char *str, char sep, char **result)
{
	int		i;
	char	*start;

	i = 0;
	while (*str)
	{
		if (*str != sep)
		{
			start = str;
			while (*str && *str != sep)
				str++;
			if (!add_word(result, start, str - start, i++))
				return (-1);
		}
		else
		{
			if (!add_word(result, str, 1, i++))
				return (-1);
			str++;
		}
	}
	result[i] = NULL;
	return (0);
}

char	**ft_split_sep(char *str, char sep)
{
	char	**result;

	result = (char **)malloc((count_words(str, sep) * 2 + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (split_loop(str, sep, result) == -1)
		return (NULL);
	return (result);
}
