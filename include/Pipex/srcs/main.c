/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:12:50 by atresall          #+#    #+#             */
/*   Updated: 2024/03/18 14:16:27 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	get_args(char *argv[], t_pipex *pipex, int argc)
{
	int	i;

	i = 0;
	pipex->args = (char ***)malloc(sizeof(char **) * argc);
	if (!pipex->args)
		perror("Malloc error");
	initerrorcode(pipex);
	pipex->path = NULL;
	while (argv[i + 1])
	{
		if (argv[i + 1][0] == '\0' && i != 0 && i != argc - 1)
		{
			pipex->errorcode[i + 1] = 1;
			pipex->path = "/";
		}
		pipex->args[i] = ft_split(argv[i + 1], ' ');
		if (!pipex->args[i])
			return (free_all(pipex), 0);
		i++;
	}
	pipex->args[i] = NULL;
	if (!check_cmd(pipex, 1) || !check_cmd(pipex, 2))
		pipex->errorcode[4] = 1;
	return (1);
}

static int	get_env_args(char *envp[], t_pipex *pipex, char **argv, int argc)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	j = 0;
	pipex->envp = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			pipex->envp = ft_split(envp[i] + 5, ':');
			while (pipex->envp[j])
			{
				temp = ft_strjoin(pipex->envp[j], "/");
				free(pipex->envp[j]);
				pipex->envp[j] = temp;
				j++;
			}
			pipex->envp[j] = NULL;
		}
	}
	if (!get_args(argv, pipex, argc))
		return (0);
	return (1);
}

static void	second_child(t_pipex *pipex)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		perror("Proc error");
	if (pipex->pid2 == 0)
	{
		if (pipex->errorcode[3] == 0)
		{
			pipex->path = check_access(pipex, 2);
			if (!pipex->path)
				print_error(2, pipex, 2);
		}
		dup2(pipex->fd[1], STDOUT_FILENO);
		dup2(pipex->fdpipe[0], STDIN_FILENO);
		close(pipex->fd[1]);
		close(pipex->fdpipe[0]);
		close(pipex->fdpipe[1]);
		execve(pipex->path, pipex->args[2], NULL);
		print_error(3, pipex, 0);
	}
}

static void	first_child(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		perror("Proc error");
	if (pipex->pid1 == 0)
	{
		if (pipex->errorcode[2] == 0)
		{
			pipex->path = check_access(pipex, 1);
			if (!pipex->path)
				print_error(2, pipex, 1);
		}
		dup2(pipex->fd[0], STDIN_FILENO);
		dup2(pipex->fdpipe[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		close(pipex->fdpipe[1]);
		close(pipex->fdpipe[0]);
		execve(pipex->path, pipex->args[1], NULL);
		print_error(1, pipex, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (1);
	if (!get_env_args(envp, &pipex, argv, argc))
		return (1);
	get_fd(&pipex, argv, argc);
	if (pipe(pipex.fdpipe) == -1)
		exit(errno);
	if (pipex.errorcode[0] == 0)
	{
		first_child(&pipex);
		close(pipex.fd[0]);
	}
	if (pipex.errorcode[1] == 0)
		second_child(&pipex);
	close_fd(&pipex, 0);
	if (pipex.errorcode[0] == 0)
		waitpid(pipex.pid1, NULL, 0);
	if (pipex.errorcode[1] == 0)
		waitpid(pipex.pid2, NULL, 0);
	free_all(&pipex);
	if (!checkerror(&pipex))
		return (errno);
	return (0);
}
