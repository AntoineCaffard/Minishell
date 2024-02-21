/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:10:47 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/09 10:12:36 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	size_t			count;
	unsigned char	*p;

	count = 0;
	p = s;
	while (count < n)
	{
		*p = 0;
		p++;
		count++;
	}
	return (s);
}
