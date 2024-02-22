/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:53:22 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/09 10:08:51 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_search;
	unsigned char	*s2_search;

	s1_search = (unsigned char *) s1;
	s2_search = (unsigned char *) s2;
	while (*s1_search == *s2_search && n - 1 > 0)
	{
		s1_search++;
		s2_search++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((int) *s1_search - (int) *s2_search);
}
