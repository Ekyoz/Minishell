/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:55:21 by atresall          #+#    #+#             */
/*   Updated: 2024/06/04 18:30:11 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		printf("\033[0;94m\033[1mTOKEN\033[0m: PIPE\n");
	else if (type == TOKEN_REDIR_IN)
		printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_IN\n");
	else if (type == TOKEN_REDIR_OUT)
		printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_OUT\n");
	else if (type == TOKEN_REDIR_APPEND)
		printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_APPEND\n");
	else if (type == TOKEN_REDIR_HEREDOC)
		printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_HEREDOC\n");
	else if (type == TOKEN_WORD)
		printf("\033[0;94m\033[1mTOKEN\033[0m: WORD\n");
	else if (type == TOKEN_OR)
		printf("\033[0;94m\033[1mTOKEN\033[0m: OR\n");
	else if (type == TOKEN_AND)
		printf("\033[0;94m\033[1mTOKEN\033[0m: AND\n");
}

void	print_list(t_token *node)
{
	int	i;

	i = 0;
	printf("\n");
	while (node != NULL)
	{
		i++;
		printf("\033[1;90m=========\033[1;0m[ Token"
			   " n %d ]\033[1;90m=========\033[0m\n",
			   i);
		print_token_type(node->type);
		if (node->type == TOKEN_WORD)
		{
			printf("\033[0;31m\033[1mCOMMAND\033[0m: %s\n", node->value[0]);
			for (int j = 1; node->value[j]; j++)
				printf("\033[0;33m\033[1mARGS[%d]\033[0m: %s\n", j,
					   node->value[j]);
		}
		if (node->type == TOKEN_REDIR_HEREDOC)
			if (node->value)
				printf("\033[0;31m\033[1mEXPANDABLE\033[0m: %s\n", node->value[0]);
		printf("\033[1;90m===============================\033[0m\n");
		printf("\n");
		node = node->next;
	}
	printf("Nombre total de tokens: \033[0;31m\033[1m%d\033[0m\n\n", i);
}

int	add_file(const char *line)
{
	int		file;
	ssize_t	len;

	file = open(".minishell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	if (line == NULL)
	{
		close(file);
		return (0);
	}
	len = write(file, line, strlen(line));
	if (len == -1)
	{
		perror("Error writing to file");
		close(file);
		return (-1);
	}
	if (write(file, "\n", 1) == -1)
	{
		perror("Error writing newline to file");
		close(file);
		return (-1);
	}
	close(file);
	return (0);
}

void	add_file_to_history(void)
{
	int		fd;
	char	buffer[1024];
	size_t	bytes_read;
	size_t	line_len;
	char	*line;
	size_t	start;
	size_t	part_len;

	fd = open(".minishell_history", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	line_len = 0;
	line = NULL;
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		start = 0;
		for (size_t i = 0; i < bytes_read; i++)
		{
			if (buffer[i] == '\n')
			{
				part_len = i - start;
				line = realloc(line, line_len + part_len + 1);
				if (line == NULL)
				{
					perror("Error reallocating memory");
					close(fd);
					return ;
				}
				memcpy(line + line_len, buffer + start, part_len);
				line_len += part_len;
				line[line_len] = '\0';
				add_history(line);
				free(line);
				line = NULL;
				line_len = 0;
				start = i + 1;
			}
		}
		if (start < bytes_read)
		{
			part_len = bytes_read - start;
			line = realloc(line, line_len + part_len + 1);
			if (line == NULL)
			{
				perror("Error reallocating memory");
				close(fd);
				return ;
			}
			memcpy(line + line_len, buffer + start, part_len);
			line_len += part_len;
			line[line_len] = '\0';
		}
	}
	if (line_len > 0)
	{
		add_history(line);
		free(line);
	}
	close(fd);
}
