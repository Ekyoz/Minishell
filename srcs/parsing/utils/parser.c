/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:07 by atresall          #+#    #+#             */
/*   Updated: 2024/05/03 17:49:20 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **extract_flags(char **command) {
	char **c_flag;
	char *first_flag = command[0];
	int i_count = -1;
	int i_flags = 1;
	int i_command = 0;
	int count = 0;

	while (command[++i_count])
		if (command[i_count][0] == '-')
			count++;

	c_flag = (char **)malloc((count + 2) * sizeof(char *));
	c_flag[0] = (char *)malloc((ft_strlen(first_flag) + 1) * sizeof(char));

	ft_strcpy(c_flag[0], first_flag);

	while (command[++i_command])
	{
		if (command[i_command][0] == '-')
		{
			c_flag[i_flags] = (char *)malloc((ft_strlen(command[i_command]) + 1) * sizeof(char));
			ft_strcpy(c_flag[i_flags], command[i_command]);
			i_flags++;
		}
		else if (command[i_command][0] != '-')
			break;
	}

	c_flag[i_flags] = NULL;

	return c_flag;
}

char **miss_elements(char **l_base, char **l_miss) {
	int i_missing = 0;
	int i_base = -1;
	int i_miss = 0;
	char **missing;
	bool find = false;

	missing = (char**)malloc((ft_strlen_array(l_base) + 1) * sizeof(char*));

	while (l_base[++i_base])
	{
		i_miss = -1;
		find = false;
		while (l_miss[++i_miss])
		{
			if (ft_strcmp(l_base[i_base], l_miss[i_miss]) == 0)
			{
				find = true;
				break;
			}
		}
		if (!find)
			missing[i_missing++] = ft_strdup(l_base[i_base]);
	}
	missing[i_missing] = NULL;

	return missing;
}

char **string_to_array(char *string)
{
	char **array;
	array = (char **)malloc(2 * sizeof(char *));
	array[0] = ft_strdup(string);
	array[1] = NULL;
	return array;
}
