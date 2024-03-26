/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:47 by atresall          #+#    #+#             */
/*   Updated: 2023/11/17 19:24:55 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmpchar(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_startcount(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && cmpchar(set, s1[i]))
		i++;
	return (i);
}

static size_t	ft_endcount(char const *s1, char const *set)
{
	size_t	i;
	size_t	k;

	k = 0;
	i = ft_strlen(s1) - 1;
	while (cmpchar(set, s1[i]))
	{
		i--;
		k++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	start;
	size_t	end;
	int		snew;
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	start = ft_startcount(s1, set);
	end = ft_endcount(s1, set);
	snew = ft_strlen(s1) - start - end;
	if ((int)snew < 0 || !s1 || start == ft_strlen(s1))
		return (ft_strdup("\0"));
	new = malloc(sizeof(char) * (snew + 1));
	if (!new)
		return (NULL);
	while (i < (size_t)snew && s1[start + i])
	{
		new[i] = s1[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
