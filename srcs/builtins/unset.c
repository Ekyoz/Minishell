/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/06/19 10:37:36 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char *str, t_env **env)
{
	t_env	*prev;
	t_env	*actual;

	actual = *env;
	prev = NULL;
	while (actual)
	{
		if (!ft_strncmp(str, actual->value, ft_strlen(str)))
		{
			if (prev)
				prev->next = actual->next;
			else
				*env = actual->next;
			free(actual->value);
			free(actual);
			return (0);
		}
		else
		{
			prev = actual;
			actual = actual->next;
		}
	}
	return (1);
}

int	do_unset(t_node *node, t_env *env)
{
	int	i;

	i = 0;
	if (!node->args[1])
		return (1);
	while (node->args[i])
	{
		unset(node->args[i], &env);
		i++;
	}
	return (1);
}
