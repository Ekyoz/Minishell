/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:02:09 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/05 16:56:30 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retourne 1 si un builtin a bien ete trouve
// je me mets pas les builtin de unset et export car il modifie ma structure
// ils ne peuvent donc pas etre dans un fork() je les execute a part
int	choose_builtin(t_token *tokens, t_tree *tree, t_node *nodes)
{
	if (!ft_strncmp(nodes->args[0], "pwd", 4))
		return (do_pwd(tree, tree->env));
	else if (!ft_strncmp(nodes->args[0], "unset", 6))
		return (do_unset(nodes, tree->env));
	else if (!ft_strncmp(nodes->args[0], "export", 6))
		return (do_export(tree, nodes));
	else if (!ft_strncmp(nodes->args[0], "env", 4))
		return (displayenv(tree->env));
	else if (!ft_strncmp(nodes->args[0], "cd", 3))
		return (do_cd(tree, nodes));
	else if (!ft_strncmp(nodes->args[0], "echo", 5))
		return (do_echo(nodes));
	else if (!ft_strncmp(nodes->args[0], "exit", 5))
		return (do_exit(tokens, tree, nodes));
	else
		return (0);
}
