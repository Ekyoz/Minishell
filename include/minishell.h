/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/03/29 14:01:39 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft.h"
# include "pipex.h"
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
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	TOKEN_WORD,      // For commands and arguments
	TOKEN_PIPE,      // For '|'
	TOKEN_REDIR_IN,  // For '<'
	TOKEN_REDIR_OUT, // For '>'
	TOKEN_REDIR_APPEND, // For '>>'
	TOKEN_REDIR_HEREDOC, // For '<<'
	TOKEN_ENV_VAR, // For environment variables
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

t_token *parsing(char *commands);
t_node *init_nodes(t_node *nodes);
int get_pipe(t_token *token, t_node *nodes);
int get_redirection_left(t_token *token, t_node *nodes);
int get_redirection_right(t_token *token, t_node *nodes);

#endif
