/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:07 by atresall          #+#    #+#             */
/*   Updated: 2024/04/23 16:30:24 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_char_before(char *string, char c, size_t pos, int len)
{
	if (pos > 0)
		if(string[pos - len] != c)
			return false;
	return true;
}

bool check_char_after(char *string, char c, size_t pos, int len)
{
	if (pos < ft_strlen(string)-1)
		if(string[pos + len] != c)
			return false;
	return true;
}


//bool check_void_after(char *string, size_t pos)
//{
////je veux checker si avant la position donner dans la string il y a des charactere
//}
//
//bool check_void_before(char *string, size_t pos)
//{
//	if (pos > 0)
//		if(string[pos - 1] == '\0')
//			return false;
//	return true;
//}

