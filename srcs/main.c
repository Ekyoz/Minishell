/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/06/18 13:39:22 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal_status = 0;

static void	argc_argv(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_token	*tokens;
	t_tree	*tree;
	t_env	*env;

	argc_argv(argc, argv);
	tokens = NULL;
	env = init_env(envp);
	add_file_to_history();
	while (true)
	{
		set_signal();
		input = readline("Minishell $ ");
		if (input == NULL)
			sig_ctrld(env);
		if (parsing(&tokens, input, env) && tokens != NULL)
		{
			print_list(tokens);
			tree = init_tree(env);
			create_node(tokens, &tree);
			clear_token(&tokens);
			ast_exec(tokens, tree);
			free_tree(&tree, 0);
		}
		free(input);
	}
}
