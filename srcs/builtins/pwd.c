/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/06/21 15:13:02 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_pwd(t_tree *tree)
{
	perror("pwd: ");
	err_free_all(tree);
	return (1);
}

char	*get_env(t_env *env, char *envvar)
{
	char	*envvalue;

	while (env)
	{
		if (!ft_strncmp(env->value, envvar, ft_strlen(envvar)))
		{
			envvalue = ft_substr(env->value, ft_strlen(envvar),
					ft_strlen(env->value) - ft_strlen(envvar));
			return (envvalue);
		}
		env = env->next;
	}
	return (NULL);
}

ssize_t	get_index_env(t_env *env, char *word)
{
	int	i;

	i = 0;
	while (env)
	{
		if (!ft_strncmp(env->value, word, ft_strlen(word)))
		{
			return (i);
		}
		i++;
		env = env->next;
	}
	return (-1);
}

// changer la valeur d'une variable d'environnement
int	set_env(t_env *env, char *var, char *value)
{
	while (env)
	{
		if (!ft_strncmp(env->value, var, ft_strlen(var)))
		{
			free(env->value);
			env->value = NULL;
			env->value = ft_strjoin(var, value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	do_pwd(t_tree *tree, t_env *env)
{
	char	pwd[1024];
	char	*path;

	while (env)
	{
		if (!ft_strncmp(env->value, "PWD=", 4))
		{
			path = ft_substr(env->value, 4, strlen(env->value) - 4);
			ft_putstr_fd(path, 1);
			ft_putchar_fd('\n', 1);
			free(path);
			return (1);
		}
		env = env->next;
	}
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		ft_putstr_fd(pwd, 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else
		error_pwd(tree);
	return (1);
}
