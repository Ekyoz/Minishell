/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:08:51 by bastpoy           #+#    #+#             */
/*   Updated: 2024/06/22 18:05:55 by bastpoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_string(t_tree *tree, t_env *env)
{
	char	**strenv;
	int		i;

	i = 0;
	strenv = (char **)malloc(sizeof(char *) * (env_length(env) + 1));
	if (!strenv)
		err_free_all(tree);
	while (env)
	{
		strenv[i] = ft_strdup(env->value);
		env = env->next;
		i++;
	}
	strenv[i] = NULL;
	return (strenv);
}

static void	print_envstr(char **str)
{
	size_t	i;
	size_t	j;
	char	equ;

	i = 0;
	while (str[i])
	{
		equ = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (str[i][j])
		{
			ft_putchar_fd(str[i][j], 1);
			if (str[i][j] == '=' && equ)
			{
				ft_putchar_fd('"', 1);
				equ--;
			}
			j++;
		}
		if (!equ)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	sort_env(char **envstr)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	while (envstr[i])
	{
		j = i + 1;
		while (envstr[j])
		{
			if (ft_strcmp(envstr[i], envstr[j]) > 0)
			{
				tmp = envstr[i];
				envstr[i] = envstr[j];
				envstr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_envstr(envstr);
	free_array(&envstr);
}

int	check_export_var(char *var, int *ret)
{
	int	i;
	int	alpha_found;

	i = 0;
	alpha_found = 0;
	if (var[0] == '=')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (ft_isalpha(var[i]))
			alpha_found = 1;
		else
		{
			if (ft_isdigit(var[i]) && !alpha_found)
				return (g_signal_status = 1, 0);
			else if (!ft_isdigit(var[i]) && var[i] != '_')
				return (0);
		}
		i++;
	}
	if (ft_strchr(var, '=') == NULL)
		return (*ret = 2, g_signal_status = 0, 0);
	return (1);
}

int	print_err_export(char *err, int *ret)
{
	ft_putstr_fd("Minihell: export:", 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	if (*ret != 2)
		g_signal_status = 1;
	return (1);
}
