/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:17:58 by bpoyet            #+#    #+#             */
/*   Updated: 2024/05/07 17:29:13 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// je check ma commande avec le chemin de ma variable d'environnement
char	*check_access1(t_tree *tree, t_node *nodes)
{
	char	*path;
	int		i;

	i = 0;
	if (!tree->envp && ft_strchr(nodes->args[0], '/') == 0)
		return (NULL);
	if (nodes->args[0] && (ft_strchr(nodes->args[0], '/') != 0
			|| ft_strncmp(nodes->args[0], ".", 1) == 0))
		return (nodes->args[0]);
	while (tree->envp[i] && nodes->args[0])
	{
		path = ft_strjoin(tree->envp[i], nodes->args[0]);
		if (!access(path, F_OK))
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

// je recuere les path de mon envp
int	get_env_args(char *envp[], t_tree *tree)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	j = 0;
	tree->envp = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			tree->envp = ft_split(envp[i] + 5, ':');
			while (tree->envp[j])
			{
				temp = ft_strjoin(tree->envp[j], "/");
				free(tree->envp[j]);
				tree->envp[j] = temp;
				j++;
			}
			tree->envp[j] = NULL;
		}
	}
	// if (!get_args(argv, pipex, argc))
	// 	return (0);
	return (1);
}

int	check_cmd1(t_tree *tree, t_node *node)
{
	char	*path;
	int		i;

	i = 0;
	if (!tree->envp && ft_strchr(node->args[0], '/') == 0)
		return (0);
	if (node->args[0] && (ft_strchr(node->args[0], '/') != 0
			|| ft_strncmp(node->args[0], ".", 1) == 0)
		&& !access(node->args[0], F_OK))
		return (1);
	while (tree->envp[i] && node->args[0][0])
	{
		path = ft_strjoin(tree->envp[i], node->args[0]);
		if (!access(path, F_OK))
		{
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	return(0);
}