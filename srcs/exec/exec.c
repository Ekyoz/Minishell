/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:48 by bpoyet            #+#    #+#             */
/*   Updated: 2024/06/21 15:29:53 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(int status, pid_t pid, int i)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_signal_status = WEXITSTATUS(status);
	}
	if (i == 1)
	{
		if (access("./.here_doc", F_OK) != -1)
			unlink("./.here_doc");
	}
}

void	*ft_execve(t_token *tokens, t_tree *tree, t_node *nodes)
{
	char	**tmp;

	tree->path = check_access1(tree, nodes);
	if (tree->fdoutcp != -1)
		close(tree->fdoutcp);
	tmp = env_to_string(tree, tree->env);
	if (execve(tree->path, nodes->args, tmp) == -1)
	{
		err_free_all3(tree, tokens, nodes, tmp);
	}
	return ((void *)0);
}

int	exec_cmd(t_token *tokens, t_tree *tree, t_node *nodes)
{
	pid_t	pid;
	int		status;
	char	**tmp;

	status = 0;
	if (choose_builtin(tokens, tree, nodes))
		return (0);
	pid = fork();
	set_signal_cmd();
	if (pid == -1)
		err_free_all(tree);
	if (pid == 0)
	{
		tree->path = check_access1(tree, nodes);
		if (!check_cmd1(tree, nodes) && !tree->path)
			print_error(tokens, CMD_NOT_FOUND, tree, nodes);
		tmp = env_to_string(tree, tree->env);
		if (execve(tree->path, nodes->args, tmp) == -1)
			err_free_all3(tree, tokens, nodes, tmp);
	}
	get_signal_cmd(status, pid);
	return (0);
}

void	exec_cmd_out(t_token *tokens, t_tree *tree, t_node *nodes)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	hdoc_or_cmd(nodes);
	if (nodes->left)
		do_unset(nodes->left, tree->env);
	if (!heredoc(tree, nodes))
		return ;
	pid = do_fork(tree, pid);
	if (pid == 0)
	{
		redir_heredoc_in(tree);
		check_redir_out(tokens, tree, nodes);
		check_redir_in(tokens, tree, nodes);
		if (!nodes->left)
			err_free_all4(tree, tokens);
		if (choose_builtin(tokens, tree, nodes->left))
			free_tree_tokens_env1(&tree, tokens);
		if (!check_cmd1(tree, nodes->left))
			print_error(tokens, CMD_NOT_FOUND, tree, nodes->left);
		ft_execve(tokens, tree, nodes->left);
	}
	parent_process(status, pid, 1);
}

void	ast_exec(t_token *tokens, t_tree *tree)
{
	t_node	*nodes;

	nodes = tree->nodes;
	if (nodes->type == TOKEN_PIPE)
	{
		exec_pipe(tokens, tree, nodes);
	}
	else if (nodes->type == TOKEN_REDIR_IN || nodes->type == TOKEN_REDIR_OUT
		|| nodes->type == TOKEN_REDIR_APPEND
		|| nodes->type == TOKEN_REDIR_HEREDOC)
	{
		exec_cmd_out(tokens, tree, nodes);
	}
	else if (nodes->type == TOKEN_WORD)
	{
		exec_cmd(tokens, tree, nodes);
	}
}
