/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:52:55 by atresall          #+#    #+#             */
/*   Updated: 2024/03/29 14:52:57 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char *input;

	while (true)
	{
		input = readline("Minishell > ");
		parsing(input);
		add_history(input);
		if(!ft_strncmp(input, "exit", 5))
			break;
	}
	return 0;
}
