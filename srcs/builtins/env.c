/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:05 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	displayenv(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
	return (1);
}

int	env_length(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env == NULL)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*init_env(char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!env_array)
		return (NULL);
	i = 0;
	env = NULL;
	new = NULL;
	while (env_array[i] != NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (0);
		new->value = ft_strndup(env_array[i], ft_strlen(env_array[i]) + 1);
		new->next = NULL;
		new->secret = 0;
		env_add_back(&env, new);
		i++;
	}
	return (env);
}
