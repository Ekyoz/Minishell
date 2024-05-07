/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/04/19 14:10:49 by atresall         ###   ########.fr       */
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

	printf("la faut rentrer\n");
	tree = init_tree(envp);
	if(!tree)
		return (1);
	while (true)
	{
		input = readline("Minishell :");
		add_history(input);
		tokens = parsing(input);
		create_node(tokens, &tree);
		printf("\n");
		print_tree(tree->nodes);
		ast_exec(tree);
		if(!ft_strncmp(input, "exit", 5))
			break;
	}
	return 0;
}