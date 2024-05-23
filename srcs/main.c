/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/05/16 16:19:22 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char *input;
	char *minishell;
	char pwd[1024];
	t_token *tokens = NULL;
	t_tree *tree;
	t_env *env;

	env = init_env(envp);
//	 displayenv(env);
	tree = init_tree(envp, env);
	if(!tree)
		return (1);
	while (true)
	{
		// minishell = ft_strjoin(ft_strdup("\n\033[0;94mMinishell\033[0m in \033[0;90m"), getcwd(pwd, sizeof(pwd)));
		minishell = ft_strdup("\n\033[0;94mMinishell\033[0m\033[0;90m");
		input = readline(ft_strjoin(minishell, "\033[0m $ "));
		if (parsing(&tokens, input, env) == false)
			continue;
		printList(tokens);
		create_node(tokens, &tree);
//		print_tree(tree->nodes);
		ast_exec(tree, envp);
		clear_token(&tokens);
		if(!ft_strncmp(input, "exit", 5))
			break;
	}
	return 0;
}
