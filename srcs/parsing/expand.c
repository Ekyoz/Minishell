/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:11:44 by atresall          #+#    #+#             */
/*   Updated: 2024/05/17 13:11:53 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char* get_env_key(char *line);
static char *get_env_value(char *key, t_env *env);
static char* replace_env(char *env, char *cmd);

char **expand(char **cmd, t_env *env)
{
    int i_cmd = -1;
    int j_cmd;
    char *var;

    while (cmd[++i_cmd])
    {
        j_cmd = -1;
        while (cmd[i_cmd][++j_cmd])
        {
            if (cmd[i_cmd][j_cmd] == '$')
            {
                var = ft_substr(cmd[i_cmd], j_cmd, ft_strlen(cmd[i_cmd]));
//                printf("VAR: %s\n", var);
//                printf("ENV: %s\n", get_env_value(ft_strtrim(var, "$"), env));
                cmd[i_cmd] = replace_env(get_env_value(ft_strtrim(var, "$"), env), cmd[i_cmd]);
            }
        }
    }
    return cmd;
}

static char *get_env_value(char *key, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(get_env_key(env->value), key) == 0)
            return ft_substr(env->value, ft_strchar(env->value, '=')+1, ft_strlen(env->value));
        env = env->next;
    }
    return NULL;
}

static char* get_env_key(char *line)
{
    int i = -1;

    while (line[++i])
        if (line[i] == '=')
            return ft_substr(line, 0, i);
    return line;
}

static char* replace_env(char *env, char *cmd)
{
    char *replaced;

    replaced = ft_strdup(ft_substr(cmd, 0, ft_strchar(cmd, '$')));
    replaced = ft_strjoin(replaced, env);
    if (!replaced)
        return "";
    return  replaced;
}
