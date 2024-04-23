/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringtab_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:41:08 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 14:29:15 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_stringtab_len(char **stringtab)
{
	size_t	i;

	if (!stringtab)
		return (0);
	i = 0;
	while (stringtab[i])
		i++;
	return (i);
}
