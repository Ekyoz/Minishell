/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:30:34 by atresall          #+#    #+#             */
/*   Updated: 2024/05/24 17:12:40 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int change_dir(char *path)
{

    if(!chdir(path))
    {
        printf("le path est change %s \n", path);
        return(1);
    }
    else
        return(0);
}

static int test_directory(char * path, int home)
{
	struct stat	st;

	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	signal_status = 1;
	if (stat(path, &st) == -1)
	{
		ft_putstr_fd(": No such file or directory", 2);
		signal_status = 127;
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n', 2);
	if (home)
		free(path);
	return (1);
}

void do_cd(t_tree *tree, t_node *node)
{
    char *homepath;
    char *path;
    char cwd[1024];

    if(node->args && node->args[1] && node->args[2])
    {
        write(2, "cd: too many arguments\n", 23);
        err_free_all(tree);
    }
    if(!node->args[1]) // dans le cas de cd tout seul
    {
        // il faut que j'aille chercher la variable d'environnement
        homepath = get_env(tree->env, "HOME=");
        if(!homepath) // je vais dans le path de HOME
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            signal_status = 1;
        }
        free(homepath);
    }
    //erreur sur le - et --
    if(node->args && !ft_strncmp(node->args[1], "-", 1)) 
    {
        ft_putstr_fd("argument not supported\n", 2);
        signal_status = 1;
    }
    // check le ~
    if(node->args && !ft_strncmp(node->args[1], "~", 1))
    {
        homepath = get_env(tree->env, "HOME="); // me renvoie le path de l'home
        if(!homepath) 
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            signal_status = 1;
            return;
        }
        path = ft_substr(node->args[1], 1, ft_strlen(node->args[1]) - 1); // je decalle de un pour enlever le tild
        path = ft_strjoin(homepath, path);
        if (change_dir(path))
            set_env(tree, tree->env, "PWD=", path);
        else
            test_directory(path, 1);
    }
    else // cd commande normal
    {
        // getcwd(NULL, 0);
        homepath = get_env(tree->env, "PWD="); // me renvoie le path de l'home
        if(!homepath) 
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            signal_status = 1;
            return;
        }
        path = NULL;
        // path = ft_strjoin(homepath, "/");
        // path = ft_strjoin(path, node->args[1]);
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            path = cwd;
        // printf("le path %s\n", path);
        if (change_dir(path))
            set_env(tree, tree->env, "PWD=", path);
        else
            test_directory(path, 1);
    }
}
