/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:17:56 by atresall          #+#    #+#             */
/*   Updated: 2024/06/04 18:47:27 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quotes_in_string(char *str, int *single_quote,
				int *double_quote, char *in_quote);
static void	check_single_quote(char *in_quote, int *single_quote);
static void	check_double_quote(char *in_quote, int *double_quote);

int	quoted(char **cmd)
{
	int		i;
	int		single_quote;
	int		double_quote;
	char	in_quote;

	i = 0;
	in_quote = 0;
	single_quote = 0;
	double_quote = 0;
	while (cmd[i])
	{
		check_quotes_in_string(cmd[i], &single_quote, &double_quote, &in_quote);
		i++;
	}
	if (single_quote == 0 && double_quote == 0)
		return (0);
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
	{
		ft_putstr_fd("Minihell: quote error\n", 2);
		return (-1);
	}
	return (1);
}

static void	check_quotes_in_string(char *str, int *single_quote,
		int *double_quote, char *in_quote)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '\'')
			check_single_quote(in_quote, single_quote);
		else if (str[j] == '"')
			check_double_quote(in_quote, double_quote);
		j++;
	}
}

static void	check_single_quote(char *in_quote, int *single_quote)
{
	if (*in_quote == 0)
	{
		(*single_quote)++;
		*in_quote = '\'';
	}
	else if (*in_quote == '\'')
	{
		(*single_quote)++;
		*in_quote = 0;
	}
}

static void	check_double_quote(char *in_quote, int *double_quote)
{
	if (*in_quote == 0)
	{
		(*double_quote)++;
		*in_quote = '"';
	}
	else if (*in_quote == '"')
	{
		(*double_quote)++;
		*in_quote = 0;
	}
}
