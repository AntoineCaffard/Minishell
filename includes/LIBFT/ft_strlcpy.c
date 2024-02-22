/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:51:31 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/09 10:06:43 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	res;
	char	*str;

	str = (char *) src;
	if (size == 0)
		return (ft_strlen(str));
	res = 0;
	if (size > 0)
	{
		while (str[res] != '\0' && res < size - 1)
		{
			dst[res] = str[res];
			res++;
		}
	}
	dst[res] = '\0';
	return (ft_strlen(str));
}
