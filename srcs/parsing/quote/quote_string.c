/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <atresall@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:42:52 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/10 17:42:52 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_string(char *str, int *len, int *s_quote, int *d_quote);
static void	handle_single_quote(int *len, int *s_quote, int *d_quote);
static void	handle_double_quote(int *len, int *s_quote, int *d_quote);

int	quote_strings(char **tableau)
{
	int	len;
	int	s_quote;
	int	d_quote;

	len = 0;
	s_quote = 0;
	d_quote = 0;
	while (*tableau)
	{
		process_string(*tableau, &len, &s_quote, &d_quote);
		tableau++;
	}
	return (len);
}

static void	process_string(char *str, int *len, int *s_quote, int *d_quote)
{
	while (*str)
	{
		if (*str == '\'')
		{
			handle_single_quote(len, s_quote, d_quote);
		}
		else if (*str == '\"')
		{
			handle_double_quote(len, s_quote, d_quote);
		}
		str++;
	}
}

static void	handle_single_quote(int *len, int *s_quote, int *d_quote)
{
	if (!*d_quote)
	{
		if (*s_quote)
		{
			*s_quote = 0;
			(*len)++;
		}
		else
		{
			*s_quote = 1;
		}
	}
}

static void	handle_double_quote(int *len, int *s_quote, int *d_quote)
{
	if (!*s_quote)
	{
		if (*d_quote)
		{
			*d_quote = 0;
			(*len)++;
		}
		else
		{
			*d_quote = 1;
		}
	}
}
