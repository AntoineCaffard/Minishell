/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:38:39 by antoine           #+#    #+#             */
/*   Updated: 2023/11/09 10:05:37 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*((char *)little))
		return ((char *) big);
	if (len == 0)
		return (NULL);
	while (i < len && ((char *)big)[i])
	{
		j = 0;
		while (((char *)little)[j] && ((char *)big)[i + j] && i + j < len)
		{
			if (((char *)little)[j] != ((char *)big)[i + j])
				break ;
			j++;
		}
		if (!((char *)little)[j])
			return (&((char *)big)[i]);
		i++;
	}
	return (NULL);
}
