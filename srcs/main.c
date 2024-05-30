/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/05/30 18:15:26 by bpoyet           ###   ########.fr       */
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

	env = init_env(envp);
	while (true)
	{
		set_signal();
		add_file_to_history();
		input = readline("\033[0;94mMinishell\033[0m\033[0;0m $ \033[0m");
		if(input == NULL) // handle ctrl + d
		{
			free_env(env);
			exit(0);
		}
		// mettre env dans tree
		// displayenv(env);
		tree = init_tree(env);
		// add_history(input);
		if(parsing(&tokens, input, env))
		{
			// printList(tokens);
			create_node(tokens, &tree);
			ast_exec(tree);
			free_tree(&tree, 0);
			clear_token(&tokens);
		}
	}
	return 0;
}
