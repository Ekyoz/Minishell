/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/05/28 16:20:51 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_char_by_index(char *str, char c)
{
	char	*ch;

	ch = ft_strchr(str, c);
	if (!ch)
		return (-1);
	return ((size_t)(ch - str));
}

static int add(t_tree *tree, t_env *env, char *word)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if(!new)
		err_free_all(tree);
	new->value = word;
	new->secret = 1;
	new->next = NULL;
	env_add_back(&env, new);
	return(1);
}

static int modify(char *word, t_env *env, ssize_t index)
{
	ssize_t i;

	i = 0;
	while(env)
	{
		if(i == index)
		{
			free(env->value);
			env->value = ft_strdup(word);
			return(1);
		}
		i++;
		env = env->next;
	}
	return(0);
}

static void put(t_tree *tree, t_env *env, char *str)
{
	size_t length;
	ssize_t index;
    char *word;
	char *strcp;

	strcp = ft_strdup(str);
	length = get_char_by_index(str, '=');
	if(length == (size_t)-1)
		length = ft_strlen(str);
	word = ft_substr(str, 0, length);
	index = get_index_env(env, word);
	free(word);
	if(index == -1)
		add(tree, env, strcp);
	else
		modify(strcp, env, index);
}

int do_export(t_tree *tree, t_node *node)
{
    char **strenv;
    int i;

    i = 1;
    if(!ft_strncmp(node->args[0], "export=", 7))
    {
        command_not_found(tree, node->args[0]);
        return(0);
    }
    if(!ft_strncmp(node->args[0], "export", 7) && !node->args[1]) // export sans arguments
    {
        strenv = env_to_string(tree, tree->env);
        sort_env(strenv);
        return(0);
    }
    while(node->args[i]) // variable a ajouter
    {
        if(!check_export_var(node->args[i]))
            return (print_err_export(node->args[i]));
		put(tree, tree->env, node->args[i]);
        i++;
    }
    return(1);
}
