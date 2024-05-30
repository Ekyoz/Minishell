/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:07:21 by Ecole42           #+#    #+#             */
/*   Updated: 2023/12/22 14:26:45 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(const char *a, const char *b, int freearg)
{
	if (a)
		free((char *)a);
	if (b && freearg == 1)
		free((char *)b);
	return (NULL);
}

char	*ft_nextoverflow(char *overflow)
{
	char	*temp;

	if (overflow)
	{
		if (gnl_strchr(overflow, '\n') && *(gnl_strchr(overflow, '\n')
				+ 1) != '\0')
		{
			temp = gnl_strdup(overflow, FREE, NONEXTBACKN);
			overflow = gnl_strdup(gnl_strchr(temp, '\n') + 1, NO_FREE,
					NONEXTBACKN);
			free(temp);
			return (overflow);
		}
		else
		{
			free(overflow);
			overflow = NULL;
			return (NULL);
		}
	}
	return (NULL);
}

char	*ft_readline(char *buffer, int fd)
{
	int		byteread;
	char	*temp;

	byteread = BUFFER_SIZE;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (ft_free(buffer, buffer, 0));
	while (!gnl_strchr(buffer, '\n') && byteread != 0)
	{
		byteread = read(fd, temp, BUFFER_SIZE);
		if (byteread == -1)
		{
			free(temp);
			return (NULL);
		}
		if (byteread != 0)
		{
			temp[byteread] = '\0';
			buffer = gnl_strjoin(buffer, temp, NO_FREE);
		}
	}
	free(temp);
	return (buffer);
}

char	*ft_modifyoverflow(char *buffer, char *overflow)
{
	char	*temp;

	if (gnl_strchr(buffer, '\n') && *(gnl_strchr(buffer, '\n') + 1) != '\0')
	{
		temp = gnl_strchr(buffer, '\n') + 1;
		overflow = gnl_strdup(temp, NO_FREE, NONEXTBACKN);
		return (overflow);
	}
	else
	{
		free(overflow);
		overflow = NULL;
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*overflow = NULL;

	buffer = NULL;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		free(overflow);
		return (overflow = NULL);
	}
	if (overflow)
		buffer = gnl_strdup(overflow, NO_FREE, NEXTBACKN);
	overflow = ft_nextoverflow(overflow);
	if (!overflow || !buffer)
	{
		buffer = ft_readline(buffer, fd);
		overflow = ft_modifyoverflow(buffer, overflow);
		buffer = gnl_strdup(buffer, FREE, NEXTBACKN);
	}
	return (buffer);
}
