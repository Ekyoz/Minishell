/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/05/23 16:27:26 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int signal_status = 0;

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char *input;
	t_token *tokens = NULL;
	t_tree *tree;
	t_env *env;

	while (true)
	{
		set_signal();
		input = readline("\n\033[0;94mMinishell\033[0m\033[0;0m $ \033[0m");
		if(input == NULL) // handle ctrl + d
		{
			free_tree(&tree);
			exit(0);
		}
		// mettre env dans tree
		env = init_env(envp);
		// displayenv(env);
		tree = init_tree(envp, env);
		// add_history(input);
		if(parsing(&tokens, input, env))
		{
			printList(tokens);
			create_node(tokens, &tree);
			ast_exec(tree, envp);
			free_tree(&tree);
			clear_token(&tokens);
		}
	}
	return 0;
}
