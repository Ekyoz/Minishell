/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/05/22 17:38:39 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
// #define _GNU_SOURCE
// #define _XOPEN_SOURCE 700

# include "libft.h"
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

extern int signal_status;

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
	char			*value;
	bool			secret;
	struct s_env	*next;
}				t_env;


typedef struct s_tree // structure qui va iterer dans mes nodes et executer les commandes
{
	t_node *nodes;
	t_env *env; // mon environnement
	char	**envp; // mes path pour les commandes
	char	*path; //  le path retourner par le check_access
	int **fdpipe; // fd de chaque pipe 
	int fdout; // fd du file out
	int fdin; // fd du file in
	int fdoutcp;
	int error[4];
	int repeatstatus;
	int status;
	pid_t pid[3];
} t_tree;


// TROUVER LES REDIRECTIONS POUR LES AJOUTER A MON ARBRE AST
int get_pipe(t_token *token, t_node *nodes);
int get_redirection_left(t_token *token, t_node *nodes);
int get_redirection_right(t_token *token, t_node *nodes);
int get_redirection_main(t_token *token, t_node *nodes);

// FONCTIONS NODES POUR CREER DES NODES SUR MON ARBRE AST
t_node *init_nodes();
t_node *add_node(t_node *nodes, t_token **token);
t_node *add_node_left(t_node *nodes, t_token **token);
t_node *add_node_right(t_node *nodes, t_token **token, bool *is_redirec);
void create_node(t_token *tokens, t_tree **tree);
void add_branches(t_token *tokens, t_node **node, t_node **nodecp, bool *redir);

//FONCTIONS MANIPULATION DE MON ARBRE
t_tree *init_tree(char *envp[], t_env *env);
void print_tree(t_node *node);

//EXECUT
void ast_exec(t_tree *tree);
void *ft_execve(t_tree *tree, t_node *nodes);
void parent_process(int status, pid_t pid);
pid_t do_fork(t_tree *tree, pid_t pid);

//PIPE
void *exec_pipe(t_tree *tree, t_node *nodes);
void close_pipe(int fd1, int fd2, int fd3, int fd4);
void first_pipe(t_tree *tree, t_node *node);
void last_pipe(t_tree *tree, t_node *node, int j);
void mid_pipe(t_tree *tree, t_node *node, int j);

//CHECKING COMMAND
char *check_access1(t_tree *tree, t_node *nodes);
int	get_env_args(char *envp[], t_tree *tree);
int	check_cmd1(t_tree *tree, t_node *node);

//REDIREC
void find_redir_out(t_tree *tree, t_node *nodes, int *isredir);
void find_redir_in(t_tree *tree, t_node *nodes, int *isredir);
void find_redir_append(t_tree *tree, t_node *nodes, int *isredir);
int check_redir_out(t_tree *tree, t_node *nodes);
int check_redir_in(t_tree *tree, t_node *nodes);
int testopening(t_tree *tree, t_node *nodes);
int testredir(t_node *nodes);

//HEREDOC
void heredoc(t_tree *tree, t_node *nodes);
bool is_heredoc(t_node *nodes);

//FONCTIONS DU GARBAGE COLLECTOR
void print_error(int errorcode, t_tree *tree, t_node *node);
void read_status(t_tree *tree);
void free_tree(t_tree *tree);
void free_env(t_env *env);
void free_pipe(int **fdpipe);

//ENVIRONNEMENT
t_env	*init_env(char **env_array);
int displayenv(t_env *env);

//BUILTIN
int choose_builtin(t_tree *tree, t_node *nodes, t_env *env);
//PWD
int getpwd_env(t_env *env);
//UNSET
int unset_export(t_node *nodes, t_env *env);
//ENV
int displayenv(t_env *env);
//EXIT
void exit_function(t_tree *tree, t_node *node);

//SIGNAUX
void set_signal(void);
void set_signal_cmd(void);
void set_signal_heredoc(void);
void get_signal_cmd(int status, pid_t pid);
void hdoc_or_cmd(t_node *nodes);

//PARSING
bool parsing(t_token **head, char *commands);
t_token *create_token(t_token_type type, char **value);
void append_token(t_token **head, t_token_type type, char **value);
void delete_token(t_token **head, t_token *node_to_delete);
bool checker(t_token **head, char *command);
t_token *get_last_token(t_token *head);
void printList(t_token * node);
void clear_list(t_token **head);
int pipe_counter(const char *command);
char **pipe_splitter(char *command);
t_token_type is_token(char *command, int pos);
int split_count(char *command);
bool there_token(char *command);
char **splitter(char *command);
char **split_token(char *command);
char **extract_flags(char **command);
char **miss_elements(char **list_base, char **list_miss);
char **string_to_array(char *string);
char **redir(char **cmd);
char **quote(char **cmd);


#endif
