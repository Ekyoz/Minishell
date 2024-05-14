/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:58:20 by atresall          #+#    #+#             */
/*   Updated: 2024/05/14 14:31:16 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type is_token(char *c, int pos)
{
	if (c[pos] == '>' && c[pos+1] == '>')
		return TOKEN_REDIR_APPEND;
	else if (c[pos] == '<' && c[pos+1] == '<')
		return TOKEN_REDIR_HEREDOC;
	else if (c[pos] == '>')
		return TOKEN_REDIR_OUT;
	else if (c[pos] == '<')
		return TOKEN_REDIR_IN;
	return TOKEN_WORD;
}

bool there_token(char *command)
{
	int i = -1;

	while (command[++i])
	{
		if (ft_strnstr(command, ">>", ft_strlen(command)))
			return true;
		if (ft_strnstr(command, "<<", ft_strlen(command)))
			return true;
		if (command[i] == '>')
			return true;
		if (command[i] == '<')
			return true;
	}
	return false;
}

char **split_token(char *command)
{
	int i;
	int i_final;
	int s_last_word;
	int e_last_word;
	char **c_final;

	i = -1;
	i_final = 0;
	s_last_word = 0;
	e_last_word = 0;
	// c_final = (char **)malloc(sizeof(char *) * split_count(command)+1);
	c_final = (char **) malloc(sizeof(char *) * (split_count(command)+1));
	if (!there_token(command))
	{
		c_final[i_final] = command;
		return c_final;
	}

	if (is_token(command, 0) != TOKEN_WORD)
	{
		if (is_token(command, 0) == TOKEN_REDIR_HEREDOC || is_token(command, 0) == TOKEN_REDIR_APPEND)
		{
			c_final[i_final++] = ft_substr(command, 0, 2);
			s_last_word+=2;
			i+=2;
			e_last_word = s_last_word;
		}
		else
		{
			c_final[i_final++] = ft_substr(command, 0, 1);
			s_last_word++;
			i++;
			e_last_word = s_last_word;
		}
	}

	while (command[++i] && i_final < (int)ft_strlen(command))
	{
		if (is_token(command, i) == TOKEN_REDIR_OUT)
		{
			c_final[i_final++] = ft_substr(command, s_last_word, e_last_word - s_last_word);
			c_final[i_final++] = ft_strdup(">");
			s_last_word = i+1;
			e_last_word = s_last_word;
		}
		else if (is_token(command, i) == TOKEN_REDIR_IN)
		{
			c_final[i_final++] = ft_substr(command, s_last_word, e_last_word - s_last_word);
			c_final[i_final++] = ft_strdup("<");
			s_last_word = i+1;
			e_last_word = s_last_word;
		}
		else if (is_token(command, i) == TOKEN_REDIR_APPEND)
		{
			c_final[i_final++] = ft_substr(command, s_last_word, e_last_word - s_last_word);
			c_final[i_final++] = ft_strdup(">>");
			s_last_word = i+2;
			e_last_word = s_last_word;
			i++;
		}
		else if (is_token(command, i) == TOKEN_REDIR_HEREDOC)
		{
			c_final[i_final++] = ft_substr(command, s_last_word, e_last_word - s_last_word);
			c_final[i_final++] = ft_strdup("<<");
			s_last_word = i+2;
			i++;
			e_last_word = s_last_word;
		}
		e_last_word++;
	}
	if (i_final < split_count(command) && is_token(command, i) == TOKEN_WORD)
		c_final[i_final++] = ft_substr(command, s_last_word, e_last_word - s_last_word);
	c_final[i_final] = NULL;
	return c_final;
}
