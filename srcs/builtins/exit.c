/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:31:39 by atresall          #+#    #+#             */
/*   Updated: 2024/05/30 16:25:04 by bpoyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi_exit(char *str, int i, int *pbm)
{
	int			j;
	long		neg;
	long long	sum;

	neg = 1;
	sum = 0;
	j = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (str[i] == ' ' || str[i] == '0'))
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++j)
	{
		sum = (sum * 10) + (str[i] - 48);
		if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
			|| ((i == 19 && neg == -1) && (str[i] == '9')))
			*pbm = 1;
		i++;
	}
	while (str[i++])
		j++;
	if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
		*pbm = 1;
	return (sum * neg);
}

static void no_numeric_msg(t_tree *tree, char *str)
{
    ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Minishell : exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
    signal_status = 1;
	free_tree(&tree, 1);
    exit(1);
}

static void many_argument_msg(t_tree *tree)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
    signal_status = 1;
	free_tree(&tree, 1);
    exit(1);
}

static void check_numeric(t_tree *tree, t_node *node)
{
	int		i;

	i = 0;
	if (node->args[1][i] == '-' || node->args[1][i] == '+')
		i++;
	while (node->args[1][i])
	{
		if (node->args[1][i] != '\f' && node->args[1][i] != '\t' && node->args[1][i] != '\r'
			&& node->args[1][i] != '\v' && node->args[1][i] != ' ')
		{
			if (node->args[1][i] < 48 || node->args[1][i] > 57)
				no_numeric_msg(tree, node->args[1]);
		}
		i++;
	}
}

int do_exit(t_tree *tree, t_node *node)
{
    int i;
    int maxlong;
    long long code;

    maxlong = 0;
    i = 0;
    if(!node->args[1]) // dans le cas ou j'ai seulement un exit
		ft_exit(tree);
    check_numeric(tree, node); //je check si l'argument est un nombre
    while(node->args[i])
        i++;
    if(i > 2) //si ++ de un argument
        many_argument_msg(tree);
    else
    {
        i = 0;
        code = ft_atoi_exit(node->args[1], i, &maxlong);
        if(maxlong == 1)
            no_numeric_msg(tree, node->args[1]);
        signal_status = code % 256;
        ft_putstr_fd("exit\n", 2);
		free_env(tree->env);
        exit(signal_status);
    }
	return(1);
}
