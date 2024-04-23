/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:43:29 by antoine           #+#    #+#             */
/*   Updated: 2023/11/09 10:05:54 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_search;
	unsigned char	*s2_search;

	s1_search = (unsigned char *) s1;
	s2_search = (unsigned char *) s2;
	while (*s1_search && *s1_search == *s2_search && n > 0)
	{
		s1_search++;
		s2_search++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((int) *s1_search - (int) *s2_search);
}
