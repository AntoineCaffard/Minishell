/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:46:34 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/09 10:08:41 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				count;
	unsigned char		*d_tranfert;
	const unsigned char	*s_tranfert;

	d_tranfert = dest;
	s_tranfert = src;
	if (d_tranfert == NULL && s_tranfert == NULL && n)
		return (0);
	count = 0;
	while (count < n)
	{
		d_tranfert[count] = (unsigned char) s_tranfert[count];
		count++;
	}
	return (dest);
}
