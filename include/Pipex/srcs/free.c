/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:11:42 by atresall          #+#    #+#             */
/*   Updated: 2024/03/18 14:16:20 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_all(t_pipex *pipex)
{
	if (pipex->errorcode[1] == 1)
	{
		ft_putstr_fd(pipex->args[3][0], 1);
		ft_putstr_fd(" : Permission denied\n", 1);
	}
	if (pipex->errorcode[1] == 2)
		ft_putstr_fd(" : No such file or directory\n", 1);
	free_threedim(pipex->args);
	free_twodim(pipex->envp);
}

void	free_threedim(char ***array)
{
	int	i;
	int	j;

	i = -1;
	if (array)
	{
		while (array[++i])
		{
			j = -1;
			while (array[i][++j])
				free(array[i][j]);
			free(array[i]);
		}
		free(array);
		array = NULL;
	}
}

void	free_twodim(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i])
		{
			free(array[i]);
		}
		free(array);
		array = NULL;
	}
}

void	close_fd(t_pipex *pipex, int stdinout)
{
	if (pipex->errorcode[0] == 0)
		close(pipex->fd[0]);
	if (pipex->errorcode[1] == 0)
		close(pipex->fd[1]);
	close(pipex->fdpipe[0]);
	close(pipex->fdpipe[1]);
	if (stdinout == 1)
	{
		close(0);
		close(1);
		close(2);
	}
}

int	checkerror(t_pipex *pipex)
{
	if (pipex->errorcode[0] == 1 || pipex->errorcode[1] == 1
		|| pipex->errorcode[2] == 1 || pipex->errorcode[3] == 1
		|| pipex->errorcode[4] == 1)
		return (0);
	return (1);
}
