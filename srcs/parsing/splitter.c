/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:54:35 by atresall          #+#    #+#             */
/*   Updated: 2024/06/10 12:32:48 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**there_token_splitter(char **c_final, char **c_space, int i_space,
				int i_final);

char	**splitter(char *command, t_env *env)
{
	int		i_space;
	int		i_final;
	char	**c_space;
	char	**c_final;

	i_space = -1;
	i_final = 0;
	c_space = ft_split_sep(command, ' ');
	c_final = (char **)malloc(sizeof(char *) * (ft_arrlen(c_space) + 1));
	if (!c_space || !command)
		return (free(c_final), NULL);
	while (c_space[++i_space])
	{
		if (!there_token(c_space[i_space]))
			c_final[i_final] = ft_strdup(c_space[i_space]);
		if (there_token(c_space[i_space]))
			c_final = there_token_splitter(c_final, c_space, i_space, i_final);
		i_final++;
	}
	c_final[i_final] = NULL;
	free_array(&c_space);
	return (quote(c_final, env, get_no_expandable(c_final), (int [2]){-1, -1}));
}

static char	**there_token_splitter(char **c_final, char **c_space, int i_space,
		int i_final)
{
	char	**c_token;
	int		i_token;

	i_token = -1;
	c_token = split_token(c_space[i_space]);
	while (c_token[++i_token])
		c_final[i_final] = ft_strdup(c_token[i_token]);
	free_array(&c_token);
	return (c_final);
}

int	split_count(char *command)
{
	int		i;
	int		count;
	bool	in_word;

	i = 0;
	count = 0;
	in_word = false;
	if (ft_strlen(command) <= 2 && is_token(command, 0) != TOKEN_WORD)
		return (1);
	while (command[i])
	{
		if (is_token(command, i) || command[i] == ' ')
			split_count_add(&in_word, &count, command, &i);
		else if (!in_word)
			in_word = true;
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

void	split_count_add(bool *in_word, int *count, char *command, int *i)
{
	if (*in_word)
	{
		*count = *count + 1;
		in_word = false;
	}
	if (is_token(command, *i))
	{
		*count = *count + 1;
		if (is_token(command, *i) == TOKEN_REDIR_APPEND || is_token(command,
				*i) == TOKEN_REDIR_HEREDOC)
			*i += 2;
		else if (is_token(command, *i) == TOKEN_REDIR_OUT || is_token(command,
				*i) == TOKEN_REDIR_IN)
			*i = *i + 1;
	}
}
