/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/06/21 15:28:28 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

# define CMD_NOT_FOUND 127
# define OPEN_FILE_ERR 128

extern int			g_signal_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_OR,
	TOKEN_AND,
	PIPEUSED,
	REDIRUSED,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			**value;
	struct s_token	*next;
}					t_token;

typedef struct s_node
{
	t_token_type	type;
	int				file_type;
	int				tree_level;
	char			**args;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_env
{
	char			*value;
	bool			secret;
	struct s_env	*next;
}					t_env;

typedef struct s_tree
{
	t_node			*head;
	t_node			*nodebegin;
	t_node			*nodes;
	t_env			*env;
	char			**envp;
	char			*path;
	int				**fdpipe;
	int				*indexj;
	int				fdout;
	int				fdin;
	int				fdoutcp;
	int				error[4];
	int				fdincp;
	int				repeatstatus;
	int				expandheredoc;
	int				status;
	pid_t			pid[1000];
}					t_tree;

//***********************************//
// 				EXEC					//
//***********************************//

void				print_array(char **array);

// TROUVER LES REDIRECTIONS POUR LES AJOUTER A MON ARBRE AST
int					get_pipe(t_token *token, t_node *nodes);
int					get_redirection_left(t_token *token, t_node *nodes,
						t_tree *tree);
int					get_redirection_right(t_token *token, t_node *nodes,
						t_tree *tree);
int					get_redirection_main(t_token *token, t_node *nodes,
						t_tree *tree);

// FONCTIONS NODES POUR CREER DES NODES SUR MON ARBRE AST
t_node				*init_nodes(t_tree *tree);
t_node				*add_node(t_node *nodes, t_token **token);
t_node				*add_node_left(t_node *nodes, t_token **token,
						t_tree *tree);
t_node				*add_node_right(t_node *nodes, t_token **token,
						bool *is_redirec, t_tree *tree);
void				create_node(t_token *tokens, t_tree **tree);
void				add_branches(t_token *tokens, t_node **node,
						t_node **nodecp, t_tree *tree);

// FONCTIONS MANIPULATION DE MON ARBRE
t_tree				*init_tree(t_env *env);

// EXECUT
void				ast_exec(t_token *tokens, t_tree *tree);
void				*ft_execve(t_token *tokens, t_tree *tree, t_node *nodes);
void				parent_process(int status, pid_t pid, int i);
pid_t				do_fork(t_tree *tree, pid_t pid);
void				dup_pipe(t_token *tokens, t_tree *tree, int j, int i);
void				parent_process_pipe(t_node **node);
int					execute_heredoc(t_tree *tree, t_token *tokens,
						t_node *nodes, int i);
void				execute_cmd(t_tree *tree, t_token *tokens, t_node *nodes,
						int i);
int					checkj(int *indexj, int j);
void				dup_and_exec(t_token *tokens, t_tree *tree, int i, int j);

// PIPE
void				exec(t_token *tokens, t_tree *tree, t_node *node);
void				exec_pipe(t_token *tokens, t_tree *tree, t_node *nodes);
void				first_pipe(t_token *tokens, t_tree *tree, t_node *node);
void				last_pipe(t_token *tokens, t_tree *tree, t_node *node,
						int j);
void				mid_pipe(t_token *tokens, t_tree *tree, t_node *node,
						int j);
void				close_all_pipes(int **fdpipe, int i);
void				wait_all_parent(t_tree *tree, int i);

// CHECKING COMMAND
char				*check_access1(t_tree *tree, t_node *nodes);
void				get_env_args(char **envp, t_tree *tree);
int					check_cmd1(t_tree *tree, t_node *node);

// REDIREC
void				find_redir_out(t_token *tokens, t_tree *tree, t_node *nodes,
						int *isredir);
void				find_redir_in(t_token *tokens, t_tree *tree, t_node *nodes,
						int *isredir);
void				find_redir_append(t_token *tokens, t_tree *tree,
						t_node *nodes, int *isredir);
int					check_redir_out(t_token *tokens, t_tree *tree,
						t_node *nodes);
int					check_redir_in(t_token *tokens, t_tree *tree,
						t_node *nodes);
int					testopening(t_token *tokens, t_tree *tree, t_node *nodes);
int					testredir(t_node *nodes);
void				redir_heredoc_in(t_tree *tree);

// HEREDOC
int					err_null_heredoc(char **eofword, int *i);
int					heredoc(t_tree *tree, t_node *nodes);
void				init_eofword(t_tree *tree, t_node *nodes, char ***eofword);
void				get_eofword(t_tree *tree, char **eofword, t_node *node,
						int *i);
void				expand_heredoc(t_tree *tree, t_node *node);
bool				is_heredoc(t_node *nodes);
int					ft_str_equals(const char *str1, const char *str2);
bool				do_heredoc(t_tree *tree, int j, int i);

// FONCTIONS DU GARBAGE COLLECTOR
void				print_error(t_token *tokens, int errorcode, t_tree *tree,
						t_node *node);
void				read_status(t_tree *tree);
void				free_tree(t_tree **tree, int env);
void				free_env(t_env *env);
void				free_envp(t_tree *tree);
void				err_free_all(t_tree *tree);
void				err_free_all1(t_tree *tree, t_token *tokens);
void				malloc_tree_err(t_env *env);
int					command_not_found(t_tree *tree, char *cmd);
void				free_array(char ***ptr);
void				ft_exit(t_tree *tree, t_token *tokens);
void				free_tree_tokens(t_tree **tree, t_token *tokens);
void				free_tree_tokens_env(t_tree **tree, t_token *tokens);
void				free_tree_tokens_env1(t_tree **tree, t_token *tokens);
void				err_free_all2(t_tree *tree, t_token *tokens);
void				err_free_all3(t_tree *tree, t_token *tokens, t_node *node,
						char **tmp);
void				err_free_all4(t_tree *tree, t_token *tokens);

// ENVIRONNEMENT
t_env				*init_env(char **env_array);
char				*get_env(t_env *env, char *envvar);
int					set_env(t_env *env, char *var, char *value);
ssize_t				get_index_env(t_env *env, char *word);
void				env_add_back(t_env **env, t_env *new);
int					env_length(t_env *env);

// BUILTIN
int					choose_builtin(t_token *tokens, t_tree *tree,
						t_node *nodes);
// PWD
int					do_pwd(t_tree *tree, t_env *env);
// UNSET
int					do_unset(t_node *node, t_env *env);
// EXPORT
int					do_export(t_tree *tree, t_node *node);
char				**env_to_string(t_tree *tree, t_env *env);
void				sort_env(char **envstr);
int					check_export_var(char *var, int *ret);
int					print_err_export(char *err, int *ret);
size_t				get_char_by_index(char *str, char c);
// ENV
int					displayenv(t_env *env);
// EXIT
int					do_exit(t_token *tokens, t_tree *tree, t_node *node);
// CD
int					do_cd(t_tree *tree, t_node *node);
// ECHO
int					do_echo(t_node *node);

// SIGNAUX
void				set_signal(void);
void				set_signal_cmd(void);
void				set_signal_heredoc(void);
void				get_signal_cmd(int status, pid_t pid);
void				hdoc_or_cmd(t_node *nodes);
void				sig_ctrld(t_env *env);

//***********************************//
// 				PARSING					//
//***********************************//

bool				parsing(t_token **head, char *commands, t_env *env);

// Token
void				append_token(t_token **head, t_token_type type,
						char **value);
void				delete_token(t_token **head, t_token *node_to_delete);
void				clear_token(t_token **head);
t_token_type		is_token(char *command, int pos);
bool				there_token(char **command, int pos);

// Pipe
int					pipe_counter(const char *command);
char				**pipe_splitter(char *command);

// Splitter
char				**splitter(char *command, t_env *env);

void				print_list(t_token *node);
char				**miss_elements(char **l_base, char **l_to_miss);
char				**string_to_array(char *string);
char				**redir(char **cmd);
char				**quote(char **cmd, t_env *env, int *no_expandable,
						int last_quote[2]);
char				**clean_space(char **cmd);
int					quoted(char **cmd);
void				get_first_quote(char **cmd, int pos[2], char *c_quote,
						int last_line[2]);
void				get_last_quote(char **cmd, int pos[2], char *c_quote,
						int last_line[2]);
char				**expand_array(char **cmd, t_env *env, int *no_expandable);
char				*expand_string(char *cmd, t_env *env);
bool				checker(t_token **head);
int					*get_no_expandable(char **cmd);
bool				is_expandable(int *no_expandable, int pos);
int					get_len_no_expand(char **cmd);
bool				do_expand(char **split, int pos);
bool				free_token(char **array1, char **array2, char **array3,
						char **array4);
bool				check_input(char *input);
bool				check_command(char **cmd);
void				free_chars(char *c1, char *c2, char *c3, char *c4);

int					add_file(const char *line);
void				add_file_to_history(void);
char				*join_quote(char *c_quoted, char *before, char *after,
						t_env *env);
char				*get_before(int first_quote[2], char **cmd);
char				*get_c_quoted(char *c_quoted, t_env *env);
char				**del_cmd(int first_quote[2], int last_quote[2],
						char **cmd);
void				get_quoted_join(char **cmd, char **quoted,
						int last_quote[2], int i_cmd);
int					quote_strings(char **tableau);
char				**split_token(char *command);
int					split_count(char *command);
void				split_count_add(bool *in_word, int *count, char *command,
						int *i);
char				*replace_env(char *env, char *cmd, char *key);
char				*get_env_value(char *key, t_env *env);
int					count_token(char *command);
int					get_int_type(t_token_type type);
int					count_heredoc(char *cmd);
void				parsing_redir(t_token **head, char **c_pipe,
						char **c_splitted, int *i_pipe);

#endif
