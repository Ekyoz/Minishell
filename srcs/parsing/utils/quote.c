/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:17:56 by atresall          #+#    #+#             */
/*   Updated: 2024/05/22 16:00:42 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//
// int quote_len(char **cmd, char quote)
// {
// 	if (quote == '"')
// 		if (get_first_quote(cmd, quote) == -1)
// 			return 0;
// 	if (quote == '\'')
// 		if (get_first_quote(cmd, quote) == -1)
// 			return 0;
//
// 	cmd = &cmd[get_first_quote(cmd, quote)];
//
// 	int i_cmd = -1;
// 	int j_cmd;
// 	int count = 0;
// 	bool b_quote = false;
//
// 	while (i_cmd < get_last_quote(cmd, quote) && cmd[++i_cmd])
// 	{
// 		j_cmd = -1;
// 		while (cmd[i_cmd][++j_cmd])
// 		{
// 			if (b_quote)
// 				count++;
// 			if (cmd[i_cmd][j_cmd] == quote)
// 			{
// 				if (cmd[i_cmd][j_cmd+1] == '\0' && i_cmd != get_last_quote(cmd, quote))
// 					count--;
// 				if (cmd[i_cmd][j_cmd+1] == quote)
// 					break;
// 				if (!b_quote)
// 					b_quote = true;
// 				else
// 				{
// 					b_quote = false;
// 					return count;
// 				}
// 				j_cmd++;
// 			}
// 		}
// 	}
// 	return count;
// }

void get_first_quote(char **cmd, int pos[2], char *c_quote)
{
	int i = -1;

	while (cmd[++i])
	{
		if (ft_strchar(cmd[i], '\'') != -1)
		{
			pos[0] = i;
			pos[1] = ft_strchar(cmd[i], '\'');
			*c_quote = '\'';
			break;
		}
		if (ft_strchar(cmd[i], '"') != -1)
		{
			pos[0] = i;
			pos[1] = ft_strchar(cmd[i], '"');
			*c_quote = '"';
			break;
		}
	}
}

void get_last_quote(char **cmd, int pos[2], char *c_quote)
{
	int i = -1;
	int j;
	int first_quote[2];

	get_first_quote(cmd, first_quote, c_quote);

	i = first_quote[0] - 1;
	j = first_quote[1] - 1;

	while (cmd[++i])
	{
		while (cmd[i][++j])
		{
			if (cmd[i][j] == *c_quote)
			{
				pos[0] = i;
				pos[1] = j;
				*c_quote = cmd[i][j];
			}
		}
		j = -1;
	}
}

bool quoted(char **cmd)
{
	int i = -1;
	int j;
	int quote_len = 0;

	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cmd[i][j] == '\'' || cmd[i][j] == '"')
				quote_len++;
		}
	}
	if (quote_len == 0)
		return false;
	if (quote_len % 2 == 0)
		return true;
	if (quote_len % 2 != 0)
	{
		cmd = ft_strjoin(cmd, readline(">"));
		return true;
	}
}

// int get_first_quote(char **cmd, char first_quote)
// {
// 	int i_cmd = -1;
// 	int s_quote = -1;
// 	int d_quote = -1;
//
// 	while (cmd[++i_cmd])
// 	{
// 		if (s_quote == -1)
// 			s_quote = ft_strchar(cmd[i_cmd], '\'');
// 		if (d_quote == -1)
// 			d_quote = ft_strchar(cmd[i_cmd], '"');
// 		if (s_quote != -1 && d_quote != -1)
// 		{
// 			if (first_quote == '"')
// 			{
// 				if (d_quote < s_quote)
// 					return i_cmd;
// 				else
// 					break;
// 			}
// 			if (first_quote == '\'')
// 			{
// 				if (s_quote < d_quote)
// 					return i_cmd;
// 				else
// 					break;
// 			}
// 		}
// 		if (first_quote == '"' && d_quote != -1)
// 			return i_cmd;
// 		if (first_quote == '\'' && s_quote != -1)
// 			return i_cmd;
// 	}
// 	return -1;
// }

// int get_last_quote(char **cmd, char last_quote)
// {
// 	int i_cmd = -1;
// 	int j_cmd;
// 	bool first = false;
//
// 	while (cmd[++i_cmd])
// 	{
// 		j_cmd = -1;
// 		while (cmd[i_cmd][++j_cmd])
// 		{
// 			if (cmd[i_cmd][j_cmd] == last_quote)
// 			{
// 				if (first)
// 					return i_cmd;
// 				else
// 					first = true;
// 			}
// 		}
// 	}
// 	return -1;
// }

char is_open(char **cmd)
{
	int single_quotes = 0;
	int double_quotes = 0;

	for (int i = 0; cmd[i] != NULL; i++) {
		char *word = cmd[i];
		int len = (int)ft_strlen(word);
		for (int j = 0; j < len; j++) {
			if (word[j] == '\'') {
				if (double_quotes % 2 == 0)
					single_quotes++;
			} else if (word[j] == '"') {
				if (single_quotes % 2 == 0)
					double_quotes++;
			}
		}
	}

	if (single_quotes % 2 != 0)
		return '\'';
	if (double_quotes % 2 != 0)
		return '"';
	else
		return 0;
}

char **add_text(char **cmd)
{
	int i_temp;
	int i;
	char *input;
	char **split;
	char **temp_cmd;

	// je doit split par les espace et ajouter les split a cmd, sauf le premier si input ne commence pas par un espace
	if (is_open(cmd) == 0)
		return cmd;
	if (is_open(cmd) != 0)
	{
		input = readline("> ");
		split = ft_split_sep(input, ' ');
		if (ft_strnstr(split[0], " ", 1))
		{
			temp_cmd = (char **) malloc(sizeof(char *) * (ft_strlen_array(cmd) + ft_strlen_array(split) + 1));
			i_temp = 0;
			i = -1;
			while (cmd[++i])
				temp_cmd[i_temp++] = cmd[i];
			i = -1;
			while (split[++i])
				temp_cmd[i_temp++] = split[i];
			temp_cmd[i_temp] = NULL;
			cmd = temp_cmd;
		}
		else
		{
			temp_cmd = (char **) malloc(sizeof(char *) * (ft_strlen_array(cmd) + ft_strlen_array(split)));
			i_temp = 0;
			i = -1;
			while (cmd[++i])
				temp_cmd[i_temp++] = cmd[i];
			temp_cmd[i_temp] = ft_strcat(temp_cmd[i_temp-1], split[0]);
			i = 0;
			while (split[++i])
				temp_cmd[i_temp++] = split[i];
			temp_cmd[i_temp] = NULL;
			cmd = temp_cmd;
		}
	}
	return cmd;
}
//
// char get_first_quote_char(char **cmd, int *l_final)
// {
// 	int s_quote;
// 	int d_quote;
// 	char first_quote = 0;
//
// 	s_quote = quote_len(cmd, '\'');
// 	d_quote = quote_len(cmd, '"');
//
// 	if (s_quote == 0 && d_quote == 0)
// 		return 0;
//
// 	if (s_quote > 0 && d_quote == 0) //si les first quote sont '
// 	{
// 		first_quote = '\'';
// 		if (l_final != NULL)
// 			*l_final = s_quote;
// 	}
// 	if (d_quote > 0 && s_quote == 0) //si les first quote sont "
// 	{
// 		first_quote = '"';
// 		if (l_final != NULL)
// 			*l_final = d_quote;
// 	}
// 	return first_quote;
// }