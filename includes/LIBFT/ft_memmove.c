/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:11:35 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/09 10:08:32 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				count;

	if ((unsigned char *) src == NULL && (unsigned char *)dest == NULL && n)
		return (0);
	count = 0;
	if ((unsigned char *) dest > (unsigned char *) src)
	{
		while (count < n)
		{
			((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1];
			n--;
		}
	}
	else
	{
		while (count < n)
		{
			((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
			count++;
		}
	}
	return (dest);
}
