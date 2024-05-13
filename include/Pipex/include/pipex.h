/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:06 by bpoyet            #+#    #+#             */
/*   Updated: 2024/03/08 13:20:45 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	***args;
	char	**envp;
	char	*path;
	int		argcount;
	int		errorcode[5];
	int		fd[2];
	int		fdpipe[2];
	pid_t	pid1;
	pid_t	pid2;
}			t_pipex;

void		free_all(t_pipex *pipex);
void		free_threedim(char ***array);
void		free_twodim(char **array);
void		initerrorcode(t_pipex *pipex);
int			checkerror(t_pipex *pipex);

int			error_code(t_pipex *pipex, char **argv, int argc, int errcode);
int			print_error(int errcode, t_pipex *pipex, int path);
char		*check_access(t_pipex *pipex, int indice);
int			check_cmd(t_pipex *pipex, int indice);
void		close_fd(t_pipex *pipex, int stdinout);
void		get_fd(t_pipex *pipex, char **argv, int argc);

#endif