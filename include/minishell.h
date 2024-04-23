/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/04/23 18:42:36 by bpoyet           ###   ########.fr       */
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
#include <stdbool.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	TOKEN_WORD, // WORD 0
	TOKEN_PIPE, // PIPE: | 1 
	TOKEN_REDIR_IN, // REDIRECTION IN: < 2
	TOKEN_REDIR_OUT, // REDIRECTION OUT: > 3
	TOKEN_REDIR_APPEND, // REDIRECTION APPEND: >> 4
	TOKEN_REDIR_HEREDOC, // REDIRECTION HEREDOC: << 5
	TOKEN_ENV_VAR, // ENV VAR: $ 6
	TOKEN_OR, // OR: || 7
	TOKEN_AND, // AND: && 8
	PIPEUSED, // 9
	REDIRUSED, // 10
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


int get_pipe(t_token *token, t_node *nodes);
int get_redirection_left(t_token *token, t_node *nodes);
int get_redirection_right(t_token *token, t_node *nodes);
int get_redirection_main(t_token *token, t_node *nodes);

t_node *init_nodes();
t_node *add_node(t_node *nodes, t_token **token);
t_node *add_node_left(t_node *nodes, t_token **token);
t_node *add_node_right(t_node *nodes, t_token **token, bool *is_redirec);
void add_branches(t_token *tokens, t_node **node, t_node **nodecp, bool *redir);
t_token *parsing(char *commands);
bool checker(t_token *head, char *command);
bool check_char_before(char *string, char c, size_t pos, int len);
bool check_char_after(char *string, char c, size_t pos, int len);

#endif
