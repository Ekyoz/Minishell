/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/06/07 15:42:17 by bastpoy          ###   ########.fr       */
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
	while (true)
	{
		set_signal();
		add_file_to_history();
		input = readline("\033[0;94mMinishell\033[0m\033[0;0m $ \033[0m");
		if (input == NULL)
			sig_ctrld(env);
		if (parsing(&tokens, input, env) && tokens != NULL)
		{
			tree = init_tree(env);
			// print_list(tokens);
			create_node(tokens, &tree);
			ast_exec(tokens, tree);
			clear_token(&tokens);
			free_tree(&tree, 0);
		}
		free(input);
	}
	return (0);
}
