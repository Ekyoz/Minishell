/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/05/31 15:50:15 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft.h"
#include "get_next_line.h"
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
	t_node *nodebegin;
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

//***********************************//
// 				EXEC				 //
//***********************************//

// TROUVER LES REDIRECTIONS POUR LES AJOUTER A MON ARBRE AST
int get_pipe(t_token *token, t_node *nodes);
int get_redirection_left(t_token *token, t_node *nodes, t_tree *tree);
int get_redirection_right(t_token *token, t_node *nodes, t_tree *tree);
int get_redirection_main(t_token *token, t_node *nodes, t_tree *tree);

// FONCTIONS NODES POUR CREER DES NODES SUR MON ARBRE AST
t_node *init_nodes(t_tree *tree);
t_node *add_node(t_node *nodes, t_token **token);
t_node *add_node_left(t_node *nodes, t_token **token, t_tree *tree);
t_node *add_node_right(t_node *nodes, t_token **token, bool *is_redirec, t_tree *tree);
void create_node(t_token *tokens, t_tree **tree);
void add_branches(t_token *tokens, t_node **node, t_node **nodecp, t_tree *tree);

//FONCTIONS MANIPULATION DE MON ARBRE
t_tree *init_tree(t_env *env);
void print_tree(t_node *node);

//EXECUT
void ast_exec(t_tree *tree);
void *ft_execve(t_tree *tree, t_node *nodes);
void parent_process(int status, pid_t pid);
pid_t do_fork(t_tree *tree, pid_t pid);

//PIPE
void *exec_pipe(t_tree *tree, t_node *nodes);
void first_pipe(t_tree *tree, t_node *node);
void last_pipe(t_tree *tree, t_node *node, int j);
void mid_pipe(t_tree *tree, t_node *node, int j);
void close_all_pipes(int **fdpipe, int i);

//CHECKING COMMAND
char *check_access1(t_tree *tree, t_node *nodes);
void	get_env_args(char **envp, t_tree *tree);
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
void err_null_heredoc(t_tree *tree, char **eofword, int i);
void heredoc(t_tree *tree, t_node *nodes);
bool is_heredoc(t_node *nodes);

//FONCTIONS DU GARBAGE COLLECTOR
void print_error(int errorcode, t_tree *tree, t_node *node);
void read_status(t_tree *tree);
void free_tree(t_tree **tree, int env);
void free_env(t_env *env);
void free_envp(t_tree *tree);
void free_pipe(t_tree *tree);
void err_free_all(t_tree *tree);
void malloc_tree_err(t_env *env);
int command_not_found(t_tree *tree, char *cmd);
void ft_free_array(void **ptr);
void ft_exit(t_tree *tree);

//ENVIRONNEMENT
t_env	*init_env(char **env_array);
char *get_env(t_env *env, char *envvar);
int set_env(t_tree *tree, t_env *env, char *var, char *value);
ssize_t get_index_env(t_env *env, char *word);
void	env_add_back(t_env **env, t_env *new);
int env_length(t_env *env);

//BUILTIN
int choose_builtin(t_tree *tree, t_node *nodes);
//PWD
int do_pwd(t_tree *tree, t_env *env);
//UNSET
int do_unset(t_node *node, t_env *env);
//EXPORT
int do_export(t_tree *tree, t_node *node);
char **env_to_string(t_tree *tree, t_env *env);
void		sort_env(char **envstr);
int check_export_var(char *var, int *ret);
int print_err_export(char *err);
size_t	get_char_by_index(char *str, char c);
//ENV
int displayenv(t_tree *tree, t_env *env);
//EXIT
int do_exit(t_tree *tree, t_node *node);
//CD
int do_cd(t_tree *tree, t_node *node);
//ECHO
int do_echo(t_node *node);

//SIGNAUX
void set_signal(void);
void set_signal_cmd(void);
void set_signal_heredoc(void);
void get_signal_cmd(int status, pid_t pid);
void hdoc_or_cmd(t_node *nodes);

//***********************************//
// 				PARSING				 //
//***********************************//

bool parsing(t_token **head, char *commands, t_env *env);

//Token
void append_token(t_token **head, t_token_type type, char **value);
void delete_token(t_token **head, t_token *node_to_delete);
void clear_token(t_token **head);
t_token_type is_token(char *command, int pos);
bool there_token(char *command);

//Pipe
int pipe_counter(const char *command);
char **pipe_splitter(char *command);

//Splitter
char **splitter(char *command, t_env *env);

void print_list(t_token * node);
char **extract_flags(char **command);
char **miss_elements(char **list_base, char **list_miss);
char **string_to_array(char *string);
char **redir(char **cmd);
char **quote(char **cmd, t_env *env);
char **clean_space(char **cmd);
bool quoted(char **cmd);
void get_first_quote(char **cmd, int pos[2], char *c_quote, int last_line[2]);
void get_last_quote(char **cmd, int pos[2], char *c_quote, int last_line[2]);
bool is_open(char **cmd, int last_line);
char **expand_array(char **cmd, t_env *env);
char *expand_string(char *cmd, t_env *env);
void checker(t_token **head);
int quote_len(char **cmd, int first_quote[2], int last_quote[2]);
void	free_array(char **array);

int add_file(const char *line);
void add_file_to_history();

#endif
