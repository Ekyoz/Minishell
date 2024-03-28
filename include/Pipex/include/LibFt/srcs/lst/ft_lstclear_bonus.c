/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:25:27 by alexandre         #+#    #+#             */
/*   Updated: 2023/11/17 15:21:32 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_next;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		temp_next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp_next;
	}
	*lst = NULL;
}
