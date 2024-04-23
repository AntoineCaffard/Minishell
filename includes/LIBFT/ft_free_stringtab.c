/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_stringtab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:20:00 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 15:49:33 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_stringtab_elements(char **to_free)
{
	size_t	i;

	i = 0;
	while (to_free[i] != NULL)
	{
		free(to_free[i]);
		i++;
	}
}

void	ft_free_stringtab(char **to_free)
{
	if (!to_free)
		return ;
	free_stringtab_elements(to_free);
	free(to_free);
}
