/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/04/23 17:14:46 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *input;
	t_token *head = NULL;

    while (true)
    {
        input = readline("Minishell$ ");
		parsing(&head, input);
		printList(head);
		clear_list(&head);
        if(!ft_strncmp(input, "exit", 5))
            break;
    }
    return 0;
}
