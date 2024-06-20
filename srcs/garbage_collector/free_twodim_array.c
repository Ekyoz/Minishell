/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_twodim_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:40:03 by bastpoy           #+#    #+#             */
/*   Updated: 2024/06/18 15:38:34 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char ***ptr)
{
	int	i;

	i = 0;
	if (*ptr)
	{
		while ((*ptr)[i])
		{
			if ((*ptr)[i])
				free((*ptr)[i]);
			(*ptr)[i] = NULL;
			i++;
		}
		free(*ptr);
		*ptr = NULL;
	}
}

bool	free_token(char **array1, char **array2, char **array3, char **array4)
{
	free_array(&array1);
	free_array(&array2);
	free_array(&array3);
	free_array(&array4);
	return (false);
}
