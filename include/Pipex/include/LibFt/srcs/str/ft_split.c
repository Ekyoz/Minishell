/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:01:11 by atresall          #+#    #+#             */
/*   Updated: 2023/11/17 19:19:19 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(const char *str, char c)
{
	int		fl;
	size_t	total;

	total = 0;
	fl = 1;
	while (*str)
	{
		if (c == *str && fl == 0)
			fl = 1;
		else if (c != *str && fl == 1)
		{
			fl = 0;
			total++;
		}
		str++;
	}
	return (total);
}

static char	*list_malloc(char const *s, char c, size_t *step)
{
	int		count;
	char	*out;

	count = 0;
	while (s[*step] == c)
	{
		*step = *step + 1;
	}
	while (s[*step] != c && s[*step])
	{
		*step = *step + 1;
		count++;
	}
	out = malloc(count * sizeof(char) + 1);
	if (!out)
		return (NULL);
	return (out);
}

static void	fill_malloc(char const *s, char c, size_t *step, char *s_m)
{
	size_t	i;

	i = 0;
	while (s[*step] == c)
	{
		*step = *step + 1;
	}
	while (s[*step] != c && s[*step])
	{
		s_m[i] = s[*step];
		*step = *step + 1;
		i++;
	}
	s_m[i] = '\0';
}

static void	*free_all(char **ptr, int i)
{
	while (i >= 0)
	{
		free(ptr[i]);
		i--;
	}
	free(ptr);
	return ((void *)0);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	step;
	size_t	j;

	i = 0;
	step = 0;
	if (!s)
		return (NULL);
	ptr = malloc(count_word(s, c) * sizeof(char *) + (1 * sizeof(char *)));
	if (!ptr)
		return (NULL);
	while (i < count_word(s, c))
	{
		j = step;
		ptr[i] = list_malloc(s, c, &step);
		if (!ptr[i])
			return (free_all(ptr, i));
		step = j;
		fill_malloc(s, c, &step, ptr[i]);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
