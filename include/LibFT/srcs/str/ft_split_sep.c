/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:49:24 by atresall          #+#    #+#             */
/*   Updated: 2024/06/05 14:47:01 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_separator(char c, char sep)
{
	return (c == sep);
}

static int	count_words(char *str, char sep)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (is_separator(*str, sep))
		{
			in_word = 0;
			count++;
		}
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		str++;
	}
	return (count);
}

static int	split_loop(char *str, char sep, char **result)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == sep)
		{
			result[j] = (char *)malloc(sizeof(char) * 2);
			result[j][0] = sep;
			result[j++][1] = '\0';
		}
		else
		{
			start = i;
			result[j] = ft_substr(str, start, ft_strchar(&str[i], sep));
			i += ft_strlen(result[j++]) - 1;
		}
		i++;
	}
	result[j] = NULL;
	return (0);
}

char	**ft_split_sep(char *str, char sep)
{
	char	**result;

	if (!str)
		return (NULL);
	result = (char **)malloc((count_words(str, sep) * 2 + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (split_loop(str, sep, result) == -1)
		return (NULL);
	return (result);
}
