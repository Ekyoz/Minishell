/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:31:38 by atresall          #+#    #+#             */
/*   Updated: 2024/06/11 17:31:38 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_token1(char *cmd, int last_word[3], char ***c_final, int *i);
static void	split_token2(char *command, int last_word[3], char ***c_final,
				int *i);
static void	split_token_3(char *command, int last_word[3], char ***c_final,
				int *i);
static void	split_token_4(char *command, int last_word[3], char ***c_final,
				int *i);

char	**split_token(char *command)
{
	int		i;
	int		last_word[3];
	char	**c_final;

	i = -1;
	last_word[2] = 0;
	last_word[0] = 0;
	last_word[1] = 0;
	c_final = (char **)malloc(sizeof(char *) * (split_count(command) + 1));
	if (!c_final)
		return (NULL);
	if (!there_token(command))
	{
		c_final[0] = command;
		c_final[1] = NULL;
		return (c_final);
	}
	split_token1(command, last_word, &c_final, &i);
	split_token2(command, last_word, &c_final, &i);
	if (last_word[2] < split_count(command) && is_token(command,
			i) == TOKEN_WORD)
		c_final[last_word[2]++] = ft_substr(command, last_word[0], last_word[1]
				- last_word[0]);
	c_final[last_word[2]] = NULL;
	return (c_final);
}

static void	split_token1(char *cmd, int last_word[3], char ***c_final, int *i)
{
	if (is_token(cmd, 0) != TOKEN_WORD)
	{
		if (is_token(cmd, 0) == TOKEN_REDIR_HEREDOC || is_token(cmd,
				0) == TOKEN_REDIR_APPEND)
		{
			*c_final[last_word[2]++] = ft_substr(cmd, 0, 2);
			last_word[0] += 2;
			*i = *i + 2;
			last_word[1] = last_word[0];
		}
		else
		{
			*c_final[last_word[2]++] = ft_substr(cmd, 0, 1);
			last_word[0]++;
			*i = *i + 1;
			last_word[1] = last_word[0];
		}
	}
}

static void	split_token2(char *command, int last_word[3], char ***c_final,
		int *i)
{
	while (command[*i] && last_word[2] < (int)ft_strlen(command))
	{
		*i = *i + 1;
		split_token_3(command, last_word, c_final, i);
		split_token_4(command, last_word, c_final, i);
		last_word[1]++;
	}
}

static void	split_token_3(char *command, int last_word[3], char ***c_final,
		int *i)
{
	if (is_token(command, *i) == TOKEN_REDIR_OUT)
	{
		*c_final[last_word[2]++] = ft_substr(command, last_word[0], last_word[1]
				- last_word[0]);
		*c_final[last_word[2]++] = ft_strdup(">");
		last_word[0] = *i + 1;
		last_word[1] = last_word[0];
	}
	else if (is_token(command, *i) == TOKEN_REDIR_IN)
	{
		*c_final[last_word[2]++] = ft_substr(command, last_word[0], last_word[1]
				- last_word[0]);
		*c_final[last_word[2]++] = ft_strdup("<");
		last_word[0] = *i + 1;
		last_word[1] = last_word[0];
	}
}

static void	split_token_4(char *command, int last_word[3], char ***c_final,
		int *i)
{
	if (is_token(command, *i) == TOKEN_REDIR_APPEND)
	{
		*c_final[last_word[2]++] = ft_substr(command, last_word[0], last_word[1]
				- last_word[0]);
		*c_final[last_word[2]++] = ft_strdup(">>");
		last_word[0] = *i + 2;
		last_word[1] = last_word[0];
		*i = *i + 1;
	}
	else if (is_token(command, *i) == TOKEN_REDIR_HEREDOC)
	{
		*c_final[last_word[2]++] = ft_substr(command, last_word[0], last_word[1]
				- last_word[0]);
		*c_final[last_word[2]++] = ft_strdup("<<");
		last_word[0] = *i + 2;
		last_word[1] = last_word[0];
		*i = *i + 1;
	}
}
