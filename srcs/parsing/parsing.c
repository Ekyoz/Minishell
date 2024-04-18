/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:52:50 by atresall          #+#    #+#             */
/*   Updated: 2024/04/18 14:07:06 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *parsing(char *commands)
{
	t_token token;
	printf("%s", commands);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	char *input;

	while (true)
	{
		input = readline("Minishell >");
		add_history(input);
		parsing(input);
		if(!ft_strncmp(input, "exit", 5))
			break;
	}
	return 0;
}