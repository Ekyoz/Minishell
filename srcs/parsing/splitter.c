/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:54:35 by atresall          #+#    #+#             */
/*   Updated: 2024/06/04 18:13:33 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **split_token(char *command);
static int split_count(char *command);
static char *check_space(char *cmd);

char **splitter(char *command, t_env *env) //splitter par les espace et par les tokens
{
	int i_space;
	int i_final;
	int i_token;
	char **c_space;
	char **c_token;
	char **c_final;

	i_space = -1;
	i_final = 0;
	c_token = NULL;
	command = check_space(command);
	c_space = ft_split_sep(command, ' ');
	c_final = (char **) malloc(sizeof(char *) * (ft_arrlen(c_space)+1));

	while (c_space[++i_space])
	{
		if (!there_token(c_space[i_space])) // si il n'y a pas de token
			c_final[i_final++] = ft_strdup(c_space[i_space]);
		if (there_token(c_space[i_space])) // si il y a un token
		{
			i_token = -1;
			c_token = split_token(c_space[i_space]);
			while (c_token[++i_token])
				c_final[i_final++] = c_token[i_token];
		}
	}
	c_final[i_final] = NULL;
	free_array(c_space);
	return quote(c_final, env, get_no_expandable(c_final));
}

static int split_count(char *command) {
	int i = 0;
	int count = 0;
	bool in_word = false;

	if (ft_strlen(command) <= 2 && is_token(command, 0) != TOKEN_WORD)
		return 1;

	while (command[i])
	{
		if (is_token(command, i) || command[i] == ' ')
		{
			if (in_word)
			{
				count++;
				in_word = false;
			}
			if (is_token(command, i))
			{
				count++;
				if (is_token(command, i) == TOKEN_REDIR_APPEND || is_token(command, i) == TOKEN_REDIR_HEREDOC)
					i+=2;
				else if (is_token(command, i) == TOKEN_REDIR_OUT || is_token(command, i) == TOKEN_REDIR_IN)
					i++;
			}
		}
		else
		if (!in_word)
			in_word = true;
		i++;
	}
	if (in_word)
		count++;
	return count;
}

static char **split_token(char *command)
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
	c_final = (char **)malloc(sizeof(char *) * (split_count(command)+1));

	if (!there_token(command))
	{
		c_final[0] = command;
        c_final[1] = NULL;
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
			e_last_word = s_last_word;
			i++;
		}
		e_last_word++;
	}
	if (i_final < split_count(command) && is_token(command, i) == TOKEN_WORD)
		c_final[i_final++] = ft_substr(command, s_last_word, e_last_word - s_last_word);
	c_final[i_final] = NULL;
	return c_final;
}

static char *check_space(char *cmd)
{
	int i = -1;

	while (cmd[++i])
	{
		if (is_token(cmd, i) == TOKEN_REDIR_APPEND || is_token(cmd, i) == TOKEN_REDIR_HEREDOC)
		{
			if (cmd[i+2] != ' ')
				cmd = ft_strjoin(ft_substr(cmd, 0, i+2), ft_strjoin(" ", ft_substr(cmd, i+2, ft_strlen(cmd)-i-2)));
			if (cmd[i-1] != ' ')
				cmd = ft_strjoin(ft_substr(cmd, 0, i), ft_strjoin(" ", ft_substr(cmd, i, ft_strlen(cmd)-i)));
			i+=2;
		}
		else if (is_token(cmd, i) == TOKEN_REDIR_OUT || is_token(cmd, i) == TOKEN_REDIR_IN)
		{
			if (cmd[i+1] != ' ')
				cmd = ft_strjoin(ft_substr(cmd, 0, i+1), ft_strjoin(" ", ft_substr(cmd, i+1, ft_strlen(cmd)-i-1)));
			if (cmd[i-1] != ' ')
				cmd = ft_strjoin(ft_substr(cmd, 0, i), ft_strjoin(" ", ft_substr(cmd, i, ft_strlen(cmd)-i)));
			i+=1;
		}
	}
	return cmd;
}
