/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/05/10 17:12:50 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *buffer, int len)
{
	char	*new;
	int		i;

	i = 0;
	while (buffer[i] && i < len)
		i++;
	new = malloc((i + 1) * sizeof(char));
	i = 0;
	while (buffer[i] && i < len)
	{
		new[i] = buffer[i];
		i++;
	}
	new[i] = '\0';
	return (new);
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
		new->value = ft_strndup(env_array[i], ft_strlen(env_array[i]));
		new->next = NULL;
		new->secret = 0;
		env_add_back(&env, new);
		i++;
	}
	return (env);
}

int displayenv(t_env *env)
{
    if(!env)
        return(1);
    while(env)
    {
        printf("%s\n", env->value);
        env = env->next;
    }
    return(0);
}

int getpwd_env(t_env *env)
{
    char pwd[1024];
    while(env)
    {
        if(!ft_strncmp(env->value, "PWD=", 4))
        {
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
        }
        env = env->next;
    }
    return(1);
}

int choose_builtin(t_node *nodes, t_env *env)
{
    fprintf(stderr, "node %s \n", nodes->args[0]);
    if(!ft_strncmp(nodes->args[0], "pwd", 3))
    {
        getpwd_env(env);
        exit(0);
    }
    else if(!ft_strncmp(nodes->args[0], "unset", 5))
    {
        unset(nodes, env);
    }
    else if(!ft_strncmp(nodes->args[0], "env", 3))
    {
        if(displayenv(env) == 1)
        {
            perror("");
            exit(errno);
        }
    }
    else
    {
        return (0);
    }
    return(0);
}