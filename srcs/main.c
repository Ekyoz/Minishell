/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/03/29 11:58:47 by bpoyet           ###   ########.fr       */
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

int main(int argc, char *argv[], char *envp[])
{
    char *input;

    while (true)
    {
        input = readline("Minishell >");
        add_history(input);
        change_directory(input);
        if(!ft_strncmp(input, "exit", 5))
            break;
    }
    return 0;
}
