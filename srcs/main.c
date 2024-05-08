/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/05/08 19:16:38 by bastpoy          ###   ########.fr       */
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

	tree = init_tree(envp);
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