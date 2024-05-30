/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:04:31 by Ecole42           #+#    #+#             */
/*   Updated: 2023/12/22 14:26:40 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define NO_FREE 0
# define FREE 1

# define NEXTBACKN 0
# define NONEXTBACKN 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	gnl_strlen(const char *str, int nextbackn);
char	*get_next_line(int fd);
void	*ft_free(const char *a, const char *b, int freearg);
char	*ft_modifyoverflow(char *buffer, char *overflow);
char	*ft_readline(char *buffer, int fd);
char	*ft_nextoverflow(char *overflow);
size_t	gnl_strlcpy(char *dest, char *src, size_t size);
char	*gnl_strjoin(char const *s1, char const *s2, int freearg);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *src, int freesrc, int nextbackn);

#endif