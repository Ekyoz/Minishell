/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/06/20 16:29:48 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal_status;

static void	argc_argv(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
}

void    print_token_type(t_token_type type)
{
    if (type == TOKEN_PIPE)
        printf("\033[0;94m\033[1mTOKEN\033[0m: PIPE\n");
    else if (type == TOKEN_REDIR_IN)
        printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_IN\n");
    else if (type == TOKEN_REDIR_OUT)
        printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_OUT\n");
    else if (type == TOKEN_REDIR_APPEND)
        printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_APPEND\n");
    else if (type == TOKEN_REDIR_HEREDOC)
        printf("\033[0;94m\033[1mTOKEN\033[0m: REDIR_HEREDOC\n");
    else if (type == TOKEN_WORD)
        printf("\033[0;94m\033[1mTOKEN\033[0m: WORD\n");
    else if (type == TOKEN_OR)
        printf("\033[0;94m\033[1mTOKEN\033[0m: OR\n");
    else if (type == TOKEN_AND)
        printf("\033[0;94m\033[1mTOKEN\033[0m: AND\n");
}

void    print_list(t_token *node)
{
    int    i;

    i = 0;
    printf("\n");
    while (node != NULL)
    {
        i++;
        printf("\033[1;90m=========\033[1;0m[ Token"
               " n %d ]\033[1;90m=========\033[0m\n",
               i);
        print_token_type(node->type);
        if (node->type == TOKEN_WORD)
        {
            printf("\033[0;31m\033[1mCOMMAND\033[0m: %s\n", node->value[0]);
            for (int j = 1; node->value[j]; j++)
                printf("\033[0;33m\033[1mARGS[%d]\033[0m: %s\n", j,
                       node->value[j]);
        }
        if (node->type == TOKEN_REDIR_HEREDOC)
            if (node->value)
                printf("\033[0;31m\033[1mEXPANDABLE\033[0m: %s\n", node->value[0]);
        printf("\033[1;90m===============================\033[0m\n");
        printf("\n");
        node = node->next;
    }
    printf("Nombre total de tokens: \033[0;31m\033[1m%d\033[0m\n\n", i);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_token	*tokens;
	t_tree	*tree;
	t_env	*env;

	g_signal_status = 0;
	argc_argv(argc, argv);
	tokens = NULL;
	env = init_env(envp);
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
			clear_token(&tokens);
            // printf("le token %p\n", tokens);
			ast_exec(tokens, tree);
			free_tree(&tree, 0);
		}
		free(input);
	}
}
