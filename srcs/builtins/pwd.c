/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/05/24 17:07:56 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		new->value = ft_strndup(env_array[i], ft_strlen(env_array[i])+1);
		new->next = NULL;
		new->secret = 0;
		env_add_back(&env, new);
		i++;
	}
	return (env);
}

char *get_env(t_env *env, char *envvar)
{
	char *envvalue;

	while(env)
	{
		if(!ft_strncmp(env->value, envvar, ft_strlen(envvar)))
		{
			envvalue = ft_substr(env->value, ft_strlen(envvar),
				ft_strlen(env->value) - ft_strlen(envvar));
			return (envvalue);
		}
		env = env->next;
	}
	return(NULL);
}


// changer la valeur d'une variable d'environnement
int set_env(t_tree *tree, t_env *env, char *var, char *value)
{
	int length;

	length  = ft_strlen(var) + ft_strlen(value);
	while(env)
	{
		if(!ft_strncmp(env->value, var, ft_strlen(var)))
		{
			free(env->value);
			env->value = NULL;
			env->value = (char *)malloc(sizeof(char) * (length + 1));
			if(!env->value)
			{
				err_free_all(tree);
			}
			// printf("var: %s value: %s\n", var, value);
			env->value = ft_strjoin(var, value);
			printf("l'env %s \n", env->value);
			return(1);
		}
		env = env->next;
	}
	return(0);
}

int getpwd_env(t_env *env)
{
    char pwd[1024];
	char *path;

    while(env)
    {
        if(!ft_strncmp(env->value, "PWD=", 4))
        {
			path = ft_substr(env->value, 4, strlen(env->value) - 4);
			ft_putstr_fd(path , 2);
			free(path);
			return(0);
        }
        env = env->next;
    }
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		printf("%s\n", pwd);
		return(0);
	}
	else
	{
		perror("");
		exit(errno);
	}
    return(1);
}
