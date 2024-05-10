/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/05/10 16:24:48 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char *input;
	t_token *tokens;
	t_tree *tree;
	t_env *env;

	env = init_env(envp);
	// displayenv(env);
	tree = init_tree(envp, env);
	if(!tree)
		return (1);
	while (true)
	{
		input = readline("Minishell :");
		add_history(input);
		tokens = parsing(input);
		create_node(tokens, &tree);
		print_tree(tree->nodes);
		printf("\n");
		ast_exec(tree);
		if(!ft_strncmp(input, "exit", 5))
			break;
	}
	return 0;
}