/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:42:21 by atresall          #+#    #+#             */
/*   Updated: 2024/03/28 09:38:27 by bpoyet           ###   ########.fr       */
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
https://code-with-me.global.jetbrains.com/O42wuVP-QTTQq8Ck6bEd0w#p=CL&fp=6B8E88527F95978E4275B0FD4ED4C4729281E6090AD2D348D281AFEF12D80B42&newUi=true
int main()
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
