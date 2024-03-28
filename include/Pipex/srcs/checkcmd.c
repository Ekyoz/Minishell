/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:18:36 by atresall          #+#    #+#             */
/*   Updated: 2024/03/18 14:16:11 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_access(t_pipex *pipex, int indice)
{
	char	*path;
	int		i;

	i = 0;
	if (!pipex->envp && ft_strchr(pipex->args[indice][0], '/') == 0)
		return (NULL);
	if (pipex->args[indice][0] && (ft_strchr(pipex->args[indice][0], '/') != 0
			|| ft_strncmp(pipex->args[indice][0], ".", 1) == 0))
		return (pipex->args[indice][0]);
	while (pipex->envp[i] && pipex->args[indice][0])
	{
		path = ft_strjoin(pipex->envp[i], pipex->args[indice][0]);
		if (!access(path, F_OK))
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

int	check_cmd(t_pipex *pipex, int indice)
{
	char	*path;
	int		i;

	i = 0;
	if (!pipex->envp && ft_strchr(pipex->args[indice][0], '/') == 0)
		return (0);
	if (pipex->args[indice][0] && (ft_strchr(pipex->args[indice][0], '/') != 0
			|| ft_strncmp(pipex->args[indice][0], ".", 1) == 0)
		&& !access(pipex->args[indice][0], F_OK))
		return (1);
	while (pipex->envp[i] && pipex->args[indice][0])
	{
		path = ft_strjoin(pipex->envp[i], pipex->args[indice][0]);
		if (!access(path, F_OK))
		{
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}
