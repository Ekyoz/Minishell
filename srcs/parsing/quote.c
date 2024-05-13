/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:28:56 by atresall          #+#    #+#             */
/*   Updated: 2024/05/13 12:28:43 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static char **get_quote(char **cmd, int (*i_simple)[2], int (*i_double)[2], bool *s_quote, bool *d_quote);
//static char **trim_quote(char **cmd);

char **quote(char **cmd)
{
//	char **l_quoted;
	int i_cmd = -1;
//	int j_cmd;
	int i_d[2][2];
	int i_s[2][2];
//	char first_quote_open;
//	char first_quote_close;
//	bool d_quote;
//	bool s_quote;

	// int for quote [a][b] = c
	// a = 0 => premier quote
	// a = 1 => derniere quote
	// b => numero de l'element de cmd
	// c => numero dans l'element cmd

	i_d[0][0] = -1;
	i_d[1][0] = -1;
	i_s[0][0] = -1;
	i_s[1][0] = -1;
//
//	for (int i = 0; i < (int)ft_strlen_array(cmd); i++)
//	{
//		printf("cmd[%d] = %s\n", i, cmd[i]);
//	}

	while (cmd[++i_cmd])
	{
//		j_cmd = -1;
		i_d[0][i_cmd] = ft_strchar(cmd[i_cmd], '\"');
		i_s[0][i_cmd] = ft_strchar(cmd[i_cmd], '\'');
		if (i_d[0][0] > -1) // double quote
		{

		}
		if (i_s[0][0] > -1) //simple quote
		{
		}
	}

//	cmd = get_quote(cmd, &i_s, &i_d, &s_quote, &d_quote);
//
//	if (s_quote || d_quote)
//		return NULL;

//	l_quoted = (char)


//	printf("i_s[0] = %d\n", i_s[0]);
//	printf("i_s[1] = %d\n", i_s[1]);
//	printf("i_d[0] = %d\n", i_d[0]);
//	printf("i_d[1] = %d\n", i_d[1]);

	return cmd;
}


//static char **get_quote(char **cmd, int (*i_simple)[2], int (*i_double)[2], bool *s_quote, bool *d_quote)
//{
//	int i_cmd = -1;
//	int j_cmd;
//
//	while (cmd[++i_cmd])
//	{
//		j_cmd = -1;
//		while (cmd[i_cmd][++j_cmd])
//		{
//			if (cmd[i_cmd][j_cmd] == '\'') // simple quote
//			{
//				*i_simple[0] = i_cmd;
//				*s_quote = true;
//			}
//			if (cmd[i_cmd][j_cmd] == '\"') // double quote
//			{
//				*i_double[0] = i_cmd;
//				*d_quote = true;
//			}
//		}
//	}
//	return cmd;
//}
