/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:30:34 by atresall          #+#    #+#             */
/*   Updated: 2024/06/10 10:52:55 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	test_directory(char *path)
{
	struct stat	st;

	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	g_signal_status = 1;
	if (stat(path, &st) == -1)
	{
		ft_putstr_fd(": No such file or directory", 2);
		g_signal_status = 127;
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

static int	change_dir(t_tree *tree, t_node *node, char *path)
{
	char	cwd[1024];

	if (!chdir(path))
	{
		getcwd(cwd, sizeof(cwd));
		set_env(tree, tree->env, "PWD=", cwd);
		return (1);
	}
	else
		test_directory(node->args[1]);
	return (0);
}

static void	tild(t_tree *tree, t_node *node, char *homepath)
{
	char	*path;

	homepath = get_env(tree->env, "HOME=");
	if (!homepath)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_signal_status = 1;
		return ;
	}
	path = ft_substr(node->args[1], 1, ft_strlen(node->args[1]) - 1);
	path = ft_strjoin(homepath, path);
	if (change_dir(tree, node, path))
		set_env(tree, tree->env, "PWD=", path);
}

static int	cd_alone(t_tree *tree, t_node *node)
{
	char	*homepath;

	homepath = get_env(tree->env, "HOME=");
	if (!homepath)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_signal_status = 1;
	}
	change_dir(tree, node, homepath);
	free(homepath);
	return (0);
}

int	do_cd(t_tree *tree, t_node *node)
{
	char	*homepath;

	homepath = NULL;
	if (node->args && node->args[1] && node->args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		err_free_all(tree);
	}
	else if (!node->args[1])
		cd_alone(tree, node);
	else if (node->args && !ft_strncmp(node->args[1], "-", 1))
	{
		ft_putstr_fd("argument not supported\n", 2);
		g_signal_status = 1;
	}
	else if (node->args && !ft_strncmp(node->args[1], "~", 1))
		tild(tree, node, homepath);
	else
		change_dir(tree, node, node->args[1]);
	return (1);
}
