/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:51:53 by bpoyet            #+#    #+#             */
/*   Updated: 2024/04/14 14:59:41 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
#include "../../include/LibFT/include/libft.h"



typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
	PIPEUSED,
	REDIRUSED,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_node
{
	t_token_type		type; //redirection ou pipe ou cmd
	int					file_type;
	bool				is_pipe; // boolean a 1 si un pipe est sur ma branche
	bool				is_redirec;
	int 				tree_level; // entier comptabilisant les sous branches
	char				**args; // ce qu'il y a dans la commande
	struct s_node	*left; 
	struct s_node	*right;
}	t_node;

typedef struct s_env
{
	char				**original_env;
	char				***parsed_env;
}	t_env;


t_node *init_nodes(t_node *nodes);
int get_pipe(t_token *token, t_node *nodes);
int get_redirection_left(t_token *token, t_node *nodes);
int get_redirection_right(t_token *token, t_node *nodes);

#endif