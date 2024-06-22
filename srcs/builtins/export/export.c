/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/06/22 18:06:21 by bastpoy          ###   ########.fr       */
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

static int	add(t_tree *tree, t_env *env, char *word)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		err_free_all(tree);
	new->value = word;
	new->secret = 1;
	new->next = NULL;
	env_add_back(&env, new);
	return (1);
}

static int	modify(char *word, t_env *env, ssize_t index)
{
	ssize_t	i;

	i = 0;
	while (env)
	{
		if (i == index)
		{
			free(env->value);
			env->value = word;
			return (1);
		}
		i++;
		env = env->next;
	}
	return (0);
}

static int	put(t_tree *tree, t_env *env, char *str, int *ret)
{
	size_t	length;
	ssize_t	index;
	char	*word;
	char	*strcp;

	if (*ret == 1)
		return (*ret = 0, 1);
	strcp = ft_strdup(str);
	length = get_char_by_index(str, '=');
	if (length == (size_t)-1)
		length = ft_strlen(str);
	word = ft_substr(str, 0, length);
	index = get_index_env(env, word);
	free(word);
	if (index == -1)
		add(tree, env, strcp);
	else
		modify(strcp, env, index);
	return (0);
}

int	do_export(t_tree *tree, t_node *node)
{
	char	**strenv;
	int		i;
	int		ret;

	ret = 0;
	i = 1;
	if (!ft_strncmp(node->args[0], "export=", 7))
		return (command_not_found(tree, node->args[0]));
	if (!ft_strncmp(node->args[0], "export", 7) && !node->args[1])
	{
		strenv = env_to_string(tree, tree->env);
		sort_env(strenv);
		return (1);
	}
	while (node->args[i])
	{
		if (!check_export_var(node->args[i], &ret))
			(print_err_export(node->args[i], &ret));
		else
			put(tree, tree->env, node->args[i], &ret);
		i++;
	}
	return (1);
}
