/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/06/07 12:01:36 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal_status = 0;

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
			ft_putstr_fd("exit\n", 1);
			free_env(env);
			exit(0);
		}
		// mettre env dans tree
		// displayenv(env);
    	// add_history(input);
		if(parsing(&tokens, input, env) && tokens != NULL)
		{
    		tree = init_tree(env);
		 	// print_list(tokens);
			create_node(tokens, &tree);
			// print_tree(tree->nodes);
			ast_exec(tokens, tree);
			clear_token(&tokens);
			free_tree(&tree, 0);
		}
		free(input);
	}
	return 0;
}
