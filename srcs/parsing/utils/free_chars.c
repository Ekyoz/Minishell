/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <atresall@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:50:56 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/07 15:50:56 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_chars(char *c1, char *c2, char *c3, char *c4)
{
	if (c1)
		free(c1);
	if (c2)
		free(c2);
	if (c3)
		free(c3);
	if (c4)
		free(c4);
}
