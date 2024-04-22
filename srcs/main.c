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

void change_directory(char *input)
{
    char buffer[1024];

    getcwd(buffer, sizeof(buffer));
    if(chdir(input) == -1)
        perror("chdir");
    getcwd(buffer, sizeof(buffer));
    printf("%s\n", buffer);
}

int main()
{
    char *input;

    while (true)
    {
        input = readline("Minishell >");
		printf("Line: %d\n", input[0]);
        add_history(input);
		parsing(input);
        if(!ft_strncmp(input, "exit", 5))
            break;
    }
    return 0;
}
