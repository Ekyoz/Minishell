/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/04/25 15:53:00 by atresall         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	TOKEN_WORD, // WORD
	TOKEN_PIPE, // PIPE: |
	TOKEN_REDIR_IN, // REDIRECTION IN: <
	TOKEN_REDIR_OUT, // REDIRECTION OUT: >
	TOKEN_REDIR_APPEND, // REDIRECTION APPEND: >>
	TOKEN_REDIR_HEREDOC, // REDIRECTION HEREDOC: <<
	TOKEN_ENV_VAR, // ENV VAR: $
	TOKEN_OR, // OR: ||
	TOKEN_AND, // AND: &&
	PIPEUSED,
	REDIRUSED,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				**value;
	struct s_token		*next;
}	t_token;

typedef struct s_node
{
	t_token_type		type; //redirection ou pipe ou cmd
	int					file_type;
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


bool parsing(t_token **head, char *commands);
t_token *create_token(t_token_type type, char **value);
void append_token(t_token **head, t_token_type type, char **value);
void delete_token(t_token **head, t_token *node_to_delete);
bool checker(t_token **head, char *command);
t_token *get_last_token(t_token *head);
void printList(t_token * node);
void clear_list(t_token **head);
int pipe_counter(const char *command);
char **pipe_spliter(char *command);
char **check_redir(char *splited_command);
t_token_type is_token(char *c, int pos);

#endif
