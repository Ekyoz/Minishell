/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/06/13 10:52:34 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal_status = 0;

static void	argc_argv(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
}

void print_node(t_node *node) {
    if (node == NULL) {
        return;
    }

    // Print the current node
    printf("Type: %d\n", node->type);
    printf("File Type: %d\n", node->file_type);
    printf("Tree Level: %d\n", node->tree_level);
    if (node->args != NULL) {
        for (int i = 0; node->args[i] != NULL; i++) {
            printf("Arg[%d]: %s\n", i, node->args[i]);
        }
    }

    // Recursively print the left and right nodes
	printf("\n\n----Left Node----\n\n");
    print_node(node->left);
	printf("\n\n----Right Node----\n\n");
    print_node(node->right);
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
			// print_list(tokens);
			tree = init_tree(env);
			create_node(tokens, &tree);
			// print_node(tree->nodes);
			ast_exec(tokens, tree);
			free_tree(&tree, 0);
			clear_token(&tokens);
		}
		free(input);
	}
}
