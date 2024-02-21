/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:21:20 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/09 10:09:03 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				count;
	const unsigned char	*s_search;

	count = 0;
	s_search = s;
	while (count < n)
	{
		if (s_search[count] == (unsigned char) c)
			return ((void *) s + count);
		count++;
	}
	return (0);
}
