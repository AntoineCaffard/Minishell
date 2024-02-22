/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stringtab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:08:32 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 14:28:19 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_stringtab(char **stringtab)
{
	size_t	i;

	if (!stringtab)
		return ;
	i = 0;
	while (stringtab[i])
	{
		ft_printf("%s\n", stringtab[i]);
		i++;
	}
}
